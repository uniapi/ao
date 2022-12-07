#!/bin/bash
#
#        Written by Ali Muhammed
#           uniapi@outlook.com
#              Nov 27, 2022
#

AO_VERSION="Assert Operator (debug-0.1.1)"

LANGS="as c nasm aarch64 riscv64"
TARGETS="x86_64 aarch64 riscv64"

AOHELP_NEW="ao new [project-name] [--verbose] [--lang language] [--proto prototype] [--defs]"
AOHELP_BUILD="ao build [--verbose] [--lang language] [--lib library] [--xflags flags] [--target target]"
AOHELP_ENCRYPT="ao encrypt <file | dir> [--cipher cipher]"
AOHELP_DECRYPT="ao decrypt <file | dir> [--cipher cipher]"
AOHELP_NOTE="ao note <file> \"opener\" \"center\" \"closer\""
AOHELP_SETUP="ao setup [--verbose] [--target target]"

ao() {
	AO_SETUP=${AO_SETUP:-"$HOME/.ao"}
	AO_INCLUDE=$AO_SETUP/include
	AO_LIB=$AO_SETUP/lib
	PLATFORM=$(uname -p)
	if [ $PLATFORM = "i386" ]; then
		if [ $(uname -s) = "SunOS" ]; then
			PLATFORM="x86_64"
		fi
	fi
	cmd="$1"
	case "$cmd" in
	"help" )
		aohelp
		;;
	"new" )
		aonew "$@"
		;;
	"build" )
		aobuild "$@"
		;;
	"encrypt" )
		aoencrypt "$@"
		;;
	"decrypt" )
		aodecrypt "$@"
		;;
	"note" )
		shift
		if [ "$1" = "help" ]; then
			if [ $# -ne 1 ]; then
				aoeexit 1 "$AOHELP_NOTE"
			fi
			aoexit "$AOHELP_NOTE"
		elif [ $# -ne 4 ]; then
			aoeexit 1 "$AOHELP_NOTE"
		fi
		aonote "$@"
		;;
	"setup" )
		aosetup "$@"
		;;
	* ) aohelp
		return 1
	esac
}

aohelp() {
	printf "%s\n" "$AO_VERSION"

	printf "\nCommands:\n"
	printf "  new\t\tCreate a new project\n"
	printf "  build\t\tBuild a project\n"
	printf "  encrypt\tEncrypt a file or directory\n"
	printf "  decrypt\tDecrypt a file or directory\n"
	printf "  note\t\tNote a file\n"
	printf "  setup\t\tSetup ao\n"
	printf "\ntype \"ao [command] help\" for more information about a command\n"
}

# aosetup [--verbose] [--target target]
#
# [-v] [--verbose]
#      [--target target]

aosetup() {
	AOHELP="$AOHELP_SETUP"
	if [ "$2" = "help" ]; then
		if [ $# -gt 2 ]; then
			aoeexit 1 "$AOHELP"
		fi
		aoexit "$AOHELP"
	fi
	while [ $# -gt 1 ]; do
		shift
		case "$1" in
		"-v" | "--verbose" )
			locked "$VERBOSE" "--verbose should be used only once!"
			VERBOSE="v"
			;;
		"--target" )
			locked "$TARGET" "--target should be used only once!"
			shift
			TARGET="$1"
			isof "$TARGET" "$TARGETS" "should use one of [$TARGETS] targets!"
			;;
		* ) aoeexit 1 "$AOHELP"
		esac
	done
	if [ ! -d $PWD/src/ao ]; then
		aoeexit 2 "$PWD does not contain src/ao"
	fi
	if [ -d $AO_SETUP ]; then
		yesno "ao: '$AO_SETUP' does already exist: update ([y]/n): " "exiting..."
	else
		mkdir -p $AO_SETUP
		verbose "mkdir -p $AO_SETUP"
	fi
# compiling, cleaning and installing libaop.so
	set_cc
	CFLAGS="-O2 -g -DDEBUG -I./src -fPIC -c"
	for c in src/ao/*.c; do
		verbose "${CC} ${CFLAGS} $c"
		${CC} ${CFLAGS} "$c"
		if [ $? -ne 0 ]; then
			exit 1
		fi
	done
	${CC} -shared -g -o libaop.so *.o
	verbose "${CC} -shared -o libaop.so *.o"
	rm -f *.o
	verbose "rm -f *.o"
	if [ ! -d $AO_LIB/$TARGET ]; then
		mkdir -p "$AO_LIB/$TARGET"
		verbose "mkdir -p $AO_LIB/$TARGET"
	fi
	mv libaop.so "$AO_LIB/$TARGET/"
	verbose "mv libaop.so $AO_LIB/$TARGET/"
# installing ao headers
	if [ ! -d $AO_INCLUDE/ao ]; then
		mkdir -p $AO_INCLUDE/ao
		verbose "mkdir -p $AO_INCLUDE/ao"
	fi
	cp src/ao/*.h $AO_INCLUDE/ao/
	verbose "cp src/ao/*.h $AO_INCLUDE/ao/"
# setting ao shell
	if [ ! -d $HOME/bin ]; then
		mkdir $HOME/bin
		verbose "mkdir $HOME/bin"
	fi
	if [ -L $HOME/bin/ao ]; then
		rm $HOME/bin/ao
		verbose "rm $HOME/bin/ao"
	fi
	cp ao.sh $AO_SETUP/ao.sh
	verbose "cp ao.sh $AO_SETUP/ao.sh"
	ln -s $AO_SETUP/ao.sh $HOME/bin/ao
	verbose "ln -s $AO_SETUP/ao.sh $HOME/bin/ao"
echo "finished"
	printf "\nremember to edit '$AO_SETUP/lib/$TARGET' path to 'LD_LIBRARY_PATH' variable\n"
}

# ao build [--lang language] [--lib library] [--xflags flags] [--target target] [--verbose]
#
# [-L] [--lang [as | c | nasm | aarch64 | riscv64]]
# [-l] [--lib <library>]
# [-x] [--xflags <flags>]
#      [--target <target>]
# [-v] [--verbose]

aobuild() {
	AOHELP="$AOHELP_BUILD"
	CC=${CC:-"gcc"}
	CFLAGS=${CFLASG:-"-O2 -g"}
	XFLAGS="-g "
	LIBAOP="aop"
	LIBS="-l$LIBAOP"
	AS=${AS:-"as"}
	LANG=""
	VERBOSE=""
	TEST="test.c"
	DATA="test.data"
	GECASE="gecase.c"
	MAIN=".main.c"
	SOLUTION=""
	EXEC="test"

	if [ "$2" = "help" ]; then
		if [ $# -gt 2 ]; then
			aoeexit 1 "$AOHELP"
		fi
		aoexit "$AOHELP"
	fi
	while [ $# -gt 1 ]; do
		shift
		case "$1" in
		"-L" | "--lang" )
			locked "$LANG" "--lang should be used only once!"
			shift
			LANG="$1"
			isof "$LANG" "$LANGS" "should use one of [$LANGS] langs!"
			;;
		"-l"* )
			LIBS="$LIBS $1"
			;;
		"--lib" )
			shift
			LIBS="$LIBS -l$1"
			;;
		"-x" | "--xflags" )
			shift
			XFLAGS="$XFLAGS $1"
			;;
		"-v" | "--verbose" )
			locked "$VERBOSE" "--verbose should be used only once!"
			VERBOSE="v"
			;;
		"--target" )
			locked "$TARGET" "--target should be used only once!"
			shift
			TARGET="$1"
			isof "$TARGET" "$TARGETS" "should use one of [$TARGETS] targets!"
			;;
		* ) aoeexit 1 "$AOHELP"
		esac
	done
	LANG=${LANG:-"as"}
# checking whether test.c exists
	if [ ! -f "$TEST" ]; then
		aoeexit 2 "test.c is not found!"
	fi
	SETUP=$(cat "$TEST" | grep -o '\([[:space:]]*int[[:space:]]\)\?[[:space:]]*setup[[:space:]]*(' | grep -o 'setup')
	AT_CASE_FAIL=$(cat "$TEST" | grep -o '[[:space:]]*void[[:space:]]\{1,\}at_case_fail[[:space:]]*(' | grep -o 'at_case_fail')
	AT_CASE_EXIT=$(cat "$TEST" | grep -o '[[:space:]]*void[[:space:]]\{1,\}at_case_exit[[:space:]]*(' | grep -o 'at_case_exit')
	AO_STATS=$(cat "$TEST" | grep -o '\([[:space:]]*int[[:space:]]\)\?[[:space:]]*ao_stats[[:space:]]*(' | grep -o 'ao_stats')
	AORUNNER=""

	printf "#include <ao/ao.h>\n" > "$MAIN"
	if [ -n "$AT_CASE_FAIL" ]; then
		printf "#include <ao/fstd.h>\n" >> "$MAIN"
		AORUNNER="ao_run"
	fi
	if [ -n "$AT_CASE_EXIT" ]; then
		printf "#include <ao/fstd.h>\n" >> "$MAIN"
		AORUNNER="ao_run"
	fi
	SETUP=${SETUP:-"NULL"}
	AT_CASE_FAIL=${AT_CASE_FAIL:-"NULL"}
	AT_CASE_EXIT=${AT_CASE_EXIT:-"NULL"}
	AO_STATS=${AO_STATS:-"NULL"}

	AOINC="AOINC_AUTO"
	AOMODE="AOMODE_STOP"

	cat "$TEST" >> "$MAIN"
# handling test.data if exists
	if [ -f "$DATA" ]; then
		printf "aop_t test()\n{\n" >> "$MAIN"
		printf "\taocase_t aoc[] = {" >> "$MAIN"
		while read -r aoc; do
			if [ -n "$aoc" ]; then
				aoc="${aoc::${#aoc}-1}"		# removing a trailing newline
				if [ "${aoc:~0}" == "\\" ]; then
					aob="${aob}${aoc::${#aoc}-1}"
					continue
				else
					aoc="${aob}${aoc}"
				fi
				printf "\n\t\t{ %s }," "$aoc" >> "$MAIN"
				aob=""
			fi
		done < "$DATA"
		printf "\n\t};\n" >> "$MAIN"
		DESCR="********* Test *********"
		NCASE="(sizeof(aoc) / sizeof(aocase_t))"
		CASESZ="sizeof(aocase_t)"
		if [ -n "$AORUNNER" ]; then
			printf "\n\tao_t ao = {" >> "$MAIN"
			printf "\n\t\t\"%s\","  "$DESCR" >> "$MAIN"
			printf "\n\t\t(void *)aoc," >> "$MAIN"
			printf "\n\t\t%s,"  "$NCASE" >> "$MAIN"
			printf "\n\t\t%s,"  "$CASESZ" >> "$MAIN"
			printf "\n\t\t(aop_t(*)(void *))assert_case," >> "$MAIN"
			printf "\n\t\t(void(*)(const void *))%s," $AT_CASE_FAIL >> "$MAIN"
			printf "\n\t\t(void(*)(void *))%s," $AT_CASE_EXIT >> "$MAIN"
			printf "\n\t\t(int(*)(void))%s," $SETUP >> "$MAIN"
			printf "\n\t\t(void(*)(const struct ao *))%s," $AO_STATS >> "$MAIN"
			printf "\n\t\t%s,"  $AOINC >> "$MAIN"
			printf "\n\t\t%s"   $AOMODE >> "$MAIN"
			printf "\n\t};\n\treturn ao_run(&ao);" >> "$MAIN"
		else
			printf "\n\treturn ao_assert(\"%s\"" "$DESCR" >> "$MAIN"
			printf ", (void *)aoc, %s, %s, (aop_t(*)(void*))assert_case);" "$NCASE" "$CASESZ" >> "$MAIN"
		fi
		printf "\n}\n" >> "$MAIN"
	fi
# handling gecase.c if exists
	if [ -f "$GECASE" ]; then
		cat "$GECASE" >> "$MAIN"
		printf "aocase_t *ao_gecase(aocase_t *aoc)\n{\n" >> "$MAIN"
		printf "\treturn aoc ? ge_case(aoc) : (aocase_t *)sizeof(aocase_t);\n" >> "$MAIN"
		printf "}\n" >> "$MAIN"
		DESCR="********* Ge Test *********"
		NCASE=$(cat "$GECASE" | grep -o "size_t[[:space:]]*ao_ncase[[:space:]]*([[:space:]]*)")
        if [ -n "$NCASE" ]; then
            NCASE="ao_ncase()"
        else
            NCASE="100"
        fi
        CASESZ="0"
		printf "aop_t getest()\n{\n" >> "$MAIN"
		if [ -n "$AORUNNER" ]; then
			printf "\n\tao_t ao = {" >> "$MAIN"
			printf "\n\t\t\"%s\","  "$DESCR" >> "$MAIN"
			printf "\n\t\t(void *)ao_gecase," >> "$MAIN"
			printf "\n\t\t%s,"  "$NCASE" >> "$MAIN"
			printf "\n\t\t%s,"  "$CASESZ" >> "$MAIN"
			printf "\n\t\t(aop_t(*)(void *))assert_case," >> "$MAIN"
			printf "\n\t\t(void(*)(const void *))%s," $AT_CASE_FAIL >> "$MAIN"
			printf "\n\t\t(void(*)(void *))%s," $AT_CASE_EXIT >> "$MAIN"
			printf "\n\t\t(int(*)(void))%s," $SETUP >> "$MAIN"
			printf "\n\t\t(void(*)(const struct ao *))%s," $AO_STATS >> "$MAIN"
			printf "\n\t\t%s,"  $AOINC >> "$MAIN"
			printf "\n\t\t%s"   $AOMODE >> "$MAIN"
			printf "\n\t};\n\treturn ao_run(&ao);" >> "$MAIN"
		else
			printf "\n\treturn ao_assert(\"%s\"" "$DESCR" >> "$MAIN"
			printf ", (void *)ao_gecase, %s, %s, (aop_t(*)(void*))assert_case);" "$NCASE" "$CASESZ" >> "$MAIN"
		fi
		printf "\n}\n" >> "$MAIN"
	fi
	printf "\n\nint main()\n{\n" >> "$MAIN"
	printf "\taop_t aop = AOP_PASS;\n" >> "$MAIN"
	if [ -f "$DATA" ]; then
		printf "\taop = test();\n" >> "$MAIN"
	fi
	if [ -f "$GECASE" ]; then
		printf "\taop = aop_cat(aop, getest());\n" >> "$MAIN"
	fi
	printf "\treturn aop;\n}\n" >> "$MAIN"

# assembling the appropriate solution
	set_target
	set_cc
	if [ $PLATFORM = $TARGET ]; then
		EXEC="test"
	else
		EXEC="$TARGET-test"
	fi
	case "$LANG" in
	"c" )
		SOLUTION="solution.c"
		if [ -f "$SOLUTION" ]; then
			$CC $CFLAGS $XFLAGS -c "$SOLUTION" -o "$SOLUTION".o
		fi
		;;
	"as" )
	# detecting as
		case "$TARGET" in
		"x86_64" )
			SOLUTION="solution-x86_64.s"
			;;
		"aarch64" )
			SOLUTION="solution-aarch64.s"
			;;
		"riscv64" )
			SOLUTION="solution-riscv64.s"
			;;
		#
		# Edit a new platform here
		#
		* ) LINE=$(($LINENO-1))
			IMPL=$(printf "\n\n\"$PLATFORM\" )\n    SOLUTION=\"solution-$PLATFORM.s\"\n    ;;\n\n")
			AOMSG=$(printf "unsupported platform! Go to the line $LINE and add the following to support it")
			aoeexit 1 "$AOMSG:$IMPL"
		esac
		if [ -f "$SOLUTION" ]; then
			$CC $CFLAGS $XFLAGS -c "$SOLUTION" -o "$SOLUTION".o
		fi
		;;
	"nasm" )
		SOLUTION="solution-nasm.s"
		if [ -f "$SOLUTION" ]; then
			nasm -f elf64 $XFLAGS "$SOLUTION" -o "$SOLUTION".o
		fi
		;;
	# guest assembly
	"riscv64" | "aarch64" )
		SOLUTION="solution-""$LANG"".s"
		if [ -f "$SOLUTION" ]; then
			$CC $CFLAGS $XFLAGS -c "$SOLUTION" -o "$SOLUTION".o
		fi
		;;
	esac
	opcode=$?
	if [ $opcode -ne 0 ]; then
		exit 1
	fi
	if [ -f "$SOLUTION".o ]; then
		$CC $CFLAGS "$MAIN" "$SOLUTION".o -I $AO_INCLUDE -L $AO_LIB/$TARGET $LIBS -o "$EXEC"
		opcode=$?
		rm -f "$SOLUTION".o
	else
		$CC $CFLAGS "$MAIN" -I $AO_INCLUDE -L $AO_LIB/$TARGET $LIBS -o "$EXEC"
		opcode=$?
	fi
	if [ $opcode -ne 0 ]; then
		exit 2
	fi
echo "done"
}

set_target() {
	if [ -z $TARGET ]; then
		case $LANG in
		"as" | "c" )
			TARGET=$PLATFORM
			;;
		"nasm" )
			TARGET="x86_64"
			;;
		"aarch64" | "riscv64" )
			TARGET=$LANG
			;;
		esac
	else
		case $TARGET in
		"x86_64" )
			case $LANG in
			"aarch64" | "riscv64" )
				aoeexit  5 "wrong target x86_64 for lang $LANG"
				;;
			esac
		;;
		"aarch64" )
			case $LANG in
			"nasm" | "riscv64" )
				aoeexit 5 "wrong target aarch64 for lang $LANG"
				;;
			esac
		;;
		"riscv64" )
			case $LANG in
			"nasm" | "aarch64" )
				aoeexit 5 "wrong target riscv64 for lang $LANG"
				;;
			esac
		;;
		esac
	fi
}

set_cc() {
	if [ -z $TARGET ]; then
		TARGET=$PLATFORM
	fi
	if [ "$TARGET" = "$PLATFORM" ]; then
		CC="gcc"
	else
		CC="${TARGET^^}_CC"
		if [ -z "${!CC}" ]; then
			aoeexit 3 "export $CC=$TARGET-your-cc-compiler to set a compiler"
		fi
		CC="${!CC}"
	fi
}

# ao new [project-name] [--lang language] [--proto prototype] [--defs] [--verbose]
#
# [-L] [--lang [as | c | nasm | aarch64 | riscv64]]
# [-p] [--proto <prototype>]
#      [--defs]
# [-v] [--verbose]

aonew() {
	AOHELP="$AOHELP_NEW"
	DIR="test"
	LANG=""
	PROTO=""
	PROTONAME=""
	DEFS=""
	VERBOSE=""
	if [ "$2" = "help" ]; then
		aoexit "$AOHELP"
	fi
# checking whether the project name is given
	if [ -n "$2" ] && [[ "$2" != -* ]] && [[ "$2" != --* ]]; then
		DIR="$2"
		shift
	fi
# handling command line arguments
	while [ $# -gt 1 ]; do
		shift
		case "$1" in
		"-L" | "--lang" )
			locked "$LANG" "--lang should be used only once!"
			shift
			LANG="$1"
			isof "$LANG" "$LANGS" "should use one of [$LANGS] langs!"
			;;
		"-p" | "--proto" )
			locked "$PROTO" "--proto should be used only once!"
			shift
			PROTO="$1"
			if [ -z "$1" ] || [[ "$1" = -* ]]; then
				aoeexit 1 "--proto should not start with '-' or be empty!"
			fi
			;;
		"--defs" )
			DEFS="$DIR/defs.h"
			;;
		"-v" | "--verbose" )
			locked "$VERBOSE" "--verbose should be used only once!"
			VERBOSE="v"
			;;
		* ) aoeexit 1 "$AOHELP"
		esac
	done
	LANG=${LANG:-"as"}
# checking whether the folder exists
	if [ -d "$DIR" ]; then
		yesno "ao: '$DIR' does already exist: override ([y]/n): "
		rm -r "$DIR"
	fi

	README="$DIR/README.md"
	TEST="$DIR/test.c"
	DATA="$DIR/test.data"
	GECASE="$DIR/gecase.c"

	mkdir "$DIR"
	verbose "  $DIR"

	printf "[Project Name](Project Link)\n\n**Note**: solutions are encrypted!" > "$README"
	verbose "  $README"

# creating test.c file
	touch "$TEST"
	verbose "  $TEST"
	aonote "$TEST" "/*" " * " " */" >> "$TEST"
	printf "\n#include <ao/aopf.h>\n" >> "$TEST"
	if [ -n "$DEFS" ]; then
# creating defs.h while creating test.c
		touch "$DEFS"
		verbose "  $DEFS"
		aonote "$DEFS" "/*" " * " " */" >> "$TEST"
		printf "\n#ifndef _DEFS_H\n#define _DEFS_H\n\n#endif\n" >> "$DEFS"
		printf "#include \"defs.h\"\n" >> "$TEST"
	fi
	printf "\n" >> "$TEST"
	if [ -n "$PROTO" ]; then
		PROTONAME=$(printf "$PROTO" | grep -Po '(\w+) *\(' | grep -Po '\w+')
	fi
	if [ -n "$PROTONAME" ]; then
		printf "extern %s;\n\n" "$PROTO" >> "$TEST"
	fi
	cat >> "$TEST" <<- EOF
typedef struct aocase {
    int sample;
    /* <type> expected; */
    /* <type> actual; */
} aocase_t;

aop_t assert_case(aocase_t *aoc)
{
    return AOP_SKIP;
}
EOF

# whether getest is needed
#	if [ "$TYPE" = "getest" ]; then
#		verbose "  $GECASE"
#		touch "$GECASE"
#		printf "#include <ge.h>\n\n" >> "$GECASE"
#		printf "aocase_t *ge_case(aocase_t *aoc)\n{\n\treturn aoc;\n}\n" >> "$GECASE"
#	else
		touch "$DATA"
		verbose "  $DATA"
#	fi
# creating solution
	case "$LANG" in
	"c" )
		proto_on_request=proto_c
		SOLUTION="$DIR/solution.c"
		touch "$SOLUTION"
		aonote "$SOLUTION" "/*" " *" " */"
		printf "\n" >> "$SOLUTION"
		if [ -n "$DEFS" ]; then
			printf "#include \"defs.h\"\n\n" >> "$DEFS"
		fi
	;;
	"as" )
		case "$PLATFORM" in
		"x86_64" )
			proto_on_request=proto_x86
			SOLUTION="$DIR/solution-x86_64.s"
			;;
		"aarch64" )
			proto_on_request=proto_aarch64
			SOLUTION="$DIR/solution-aarch64.s"
			;;
		"riscv64" )
			proto_on_request=proto_riscv64
			SOLUTION="$DIR/solution-riscv64.s"
			;;
		#
		# Edit a new platform here
		#
		* ) LINE=$(($LINENO-1))
			IMPL=$(printf "\n\n\"$PLATFORM\" )\n    SOLUTION=\"\$DIR/solution-$PLATFORM.s\"\n    ;;\n\n")
			AOMSG=$(printf "unsupported platform! Go to the line $LINE and add the following to support it")
			aoeexit 1 "$AOMSG:$IMPL"
		esac
		touch "$SOLUTION"
		aonote "$SOLUTION" "/*" " *" " */"
	;;
	"nasm" )
		proto_on_request=proto_nasm
		SOLUTION="$DIR/solution-nasm.s"
		touch "$SOLUTION"
		aonote "$SOLUTION" ";" "; " ";"
	;;
	"aarch64" )
		proto_on_request=proto_aarch64
		SOLUTION="$DIR/solution-aarch64.s"
		touch "$SOLUTION"
		aonote "$SOLUTION" "/*" " * " " */"
		printf "\n" >> "$SOLUTION"
	;;
	"riscv64" )
		proto_on_request=proto_riscv64
		SOLUTION="$DIR/solution-riscv64.s"
		touch "$SOLUTION"
		aonote "$SOLUTION" "/*" " * " " */"
		printf "\n" >> "$SOLUTION"
	;;
	esac
	$proto_on_request
	verbose "  $SOLUTION"
}

dt() {
    printf "%s" "$(date "+%b %-d, %Y")"
}

yesno() {
	ANS="?"
	while [ "$ANS" != "y" ] && [ "$ANS" != "n" ]; do
		read -p "$1" -n1 ANS
		if [ "$ANS" = "" ]; then
			ANS=$(printf "%s\n" "$1" | grep -o '\[[YyNn]\]' | grep -o [YyNn])
			break
		fi
		printf "\n"
		ANS=`printf "$ANS" | tr '[:upper:]' '[:lower:]'`
	done
	if [ "$ANS" == "n" ]; then
		if [ "$2" != "" ]; then
			printf "$2\n"
		fi
		exit 1
	fi
}

isof() {
	WHAT="$1"
	OF="$2"
	for what in $OF; do
		if [ "$WHAT" = "$what" ]; then
			return 0
		fi
	done
	aoeexit 1 "$3"
}

locked() {
	WHAT="$1"
	if [ -n "$WHAT" ]; then
		aoeexit 1 "$2"
	fi
}

verbose() {
	if [ -n "$VERBOSE" ]; then
		printf "%s\n" "$1"
	fi
}

proto_c() {
	if [ -n "$PROTONAME" ]; then
		printf "%s\n{\n\n}\n" "$PROTO" >> "$SOLUTION"
	fi
}

proto_nasm() {
	if [ -n "$PROTONAME" ]; then
		printf "global %s\n\n" "$PROTONAME" >> "$SOLUTION"
		printf "; <-- %s -->\n" "$PROTO" >> "$SOLUTION"
		printf "%s:\n\tret\n" "$PROTONAME" >> "$SOLUTION"
		printf "; -----> endof %s <-----\n" "$PROTONAME" >> "$SOLUTION"
	fi
}

proto_x86() {
	if [ -n "$PROTONAME" ]; then
		printf ".global %s\n\n" "$PROTONAME" >> "$SOLUTION"
		printf "# <-- %s -->\n" "$PROTO"$ >> "$SOLUTION"
		printf "%s:\n\tret\n" "$PROTONAME" >> "$SOLUTION"
		printf "# -----> endof %s <-----\n" "$PROTONAME" >> "$SOLUTION"
	fi
}

proto_aarch64() {
	if [ -n "$PROTONAME" ]; then
		printf ".global %s\n\n" "$PROTONAME" >> "$SOLUTION"
		printf "# <-- %s -->\n" "$PROTO"$ >> "$SOLUTION"
		printf "%s:\n\tret\n" "$PROTONAME" >> "$SOLUTION"
		printf "# -----> endof %s <-----\n" "$PROTONAME" >> "$SOLUTION"
	fi
}

proto_riscv64() {
	if [ -n "$PROTONAME" ]; then
		printf ".global %s\n\n" "$PROTONAME" >> "$SOLUTION"
		printf "# <-- %s -->\n" "$PROTO" >> "$SOLUTION"
		printf "%s:\n\tret\n" "$PROTONAME" >> "$SOLUTION"
		printf "# -----> endof %s <-----\n" "$PROTONAME" >> "$SOLUTION"
	fi
}

# aonote FILE OPENER CENTER CLOSER
aonote() {
	FILE="$1"
	OPENER="$2"
	CENTER="$3"
	CLOSER="$4"
	IDENT=${6:-8}
	if [ -z "$NOTE" ]; then
		if [ -z "$AUTHOR" ]; then
			if command -v git &> /dev/null; then
				AUTHOR=`git config user.name`
				if [ -z "$EMAIL" ]; then
					EMAIL=`git config user.email`
				fi
			else
				return 1
			fi
		fi
		DATE=`dt`
		NOTE=`printf "Written by %s\n%s\n%s" "$AUTHOR" "$EMAIL" "$DATE"`
	fi
#	MAXLEN=`printf "$NOTE" | wc -L`
# SunOS and AIX does not support: "wc -L"
	MAXLEN=`printf "$NOTE" | awk '{ if (length > n) { n = length }}END{ print n }'`
	printf "%s\n" "$OPENER" >> "$FILE"

	printf "%s\n" "$NOTE" |
	while read line; do
       	if [ ! "$line" = "" ]; then
			N=$IDENT
			if [ $MAXLEN -ne ${#line} ]; then
				N=$(($N+$MAXLEN-($MAXLEN+${#line}>>1)))
			fi
			printf "%s%*s%s\n" "$CENTER" $N "" "$line" >> "$FILE"
       	fi
	done
	printf "%s\n" "$CLOSER" >> "$FILE"
}

aocipher() {
	CIPHER=""
# handling command line arguments
    while [ $# -gt 2 ]; do
        shift
        case "$2" in
       "-c" | "--cipher" )
            locked "$CIPHER" "<cipher> can be used only once!"
            shift
            CIPHER="$2"
			if [ -z "$CIPHER" ]; then
				aoeexit 1 "<cipher> should be passed after the key"
			fi
            ;;
		* ) aoeexit 1 "$AOHELP"
		esac
	done
# checking whether openssl is available
	VERSION=$(2>&1 openssl version)
	opcode=$?
	if [ $opcode -ne 0 ]; then
		aoeexit 1 "openssl is not found"
	fi
	VERSION=$(printf "$VERSION" | grep -o '1.0.[0-9]\{1,\}')
	if [ -n "$VERSION" ]; then
		aoeexit 1 "upgrade openssl to version at least 1.1.1"
	fi
# checking whether cipher does exist
	if [ -n "${CIPHER}" ]; then
		if ! openssl enc -list "${CIPHER}" | grep -o "${CIPHER}" &> /dev/null; then
			aoeexit 1 "${CIPHER} is not supported by openssl"
		fi
	else
		CIPHER="aes-256-cbc"
	fi
	printf "$CIPHER"
}


# ao encrypt <file | dir> [--cipher cipher]
#
# [-c] [--cipher <cipher>]

aoencrypt() {
	ENC="$2"
	AOHELP="$AOHELP_ENCRYPT"
# whether arguments are given
	if [ $# -lt 2 ] || [[ "$ENC" = -* ]]; then
		aoeexit 1 "$AOHELP"
	fi
# checking whether ao encrypt help is needed
    if [ "$2" = "help" ]; then
		if [ $# -ne 2 ]; then
	        aoeexit 1 "$AOHELP"
		else
			aoexit "$AOHELP"
		fi
    fi
# checking existence
	if [ ! -f "$ENC" ] && [ ! -d "$ENC" ]; then
		aoeexit 1 "$ENC does not exist!"
	fi
	CIPHER=`aocipher "$@"`
	opcode=$?
	if [ $opcode -ne 0 ]; then
		exit $opcode
	fi
# encrypting
	if [ -d "$ENC" ]; then
		if ! command -v tar &> /dev/null; then
			aoeexit 1 "tar is not found"
		fi
		tar cf - "$ENC" | openssl enc -"$CIPHER" -e -pbkdf2 -out "$ENC.enc"
		opcode=$?
		if [ $opcode -ne 0 ]; then
			aoeexit 1 "empty password"
		fi
	else
		openssl enc -"$CIPHER" -e -pbkdf2 -in "$ENC" -out "$ENC.enc"
		opcode=$?
		if [ $opcode -ne 0 ]; then
			aoeexit 1 "empty password"
		fi
	fi
}

# ao decrypt <file | dir> [--cipher cipher]
#
# [-c] [--cipher <cipher>]

aodecrypt() {
	DEC="$2"
	AOHELP="$AOHELP_DECRYPT"
# whether arguments are given
	if [ $# -lt 2 ] || [[ "$DEC" = -* ]]; then
		aoeexit 1 "$AOHELP"
	fi
# whether ao encrypt help is needed
    if [ "$DEC" = "help" ]; then
		if [ $# -ne 2 ]; then
	        aoeexit 1 "$AOHELP"
		else
			aoexit "$AOHELP"
		fi
    fi
# whether the decryption element is .enc
	if [[ "$DEC" != *.enc ]]; then
		aoeexit 1 "$DEC is not .enc"
	fi
# checking existence
	if [ ! -f "$DEC" ]; then
		aoeexit 1 "$DEC does not exist"
	fi

	DEC="${DEC%.enc}"
# whether target already exists
	if [ -f "$DEC" ] || [ -d "$DEC" ]; then
		yesno "ao: '$DEC' does already exist: override ([y]/n): "
		mv "$DEC" ".$DEC.old"
	fi
	CIPHER=`aocipher "$@"`
	opcode=$?
	if [ $opcode -ne 0 ]; then
		exit $opcode
	fi
	if ! command -v tar &> /dev/null; then
		aoeexit 1 "tar is not found"
	fi
# decrypting
	outp=$(2>&1 openssl enc -"$CIPHER" -d -pbkdf2 -in "$DEC.enc" -out ".$DEC")
	opcode=$?
	if printf "$outp" | grep -o "bad decrypt" &> /dev/null; then
		aoeexit 1 "wrong password"
	fi
	if [ $opcode -ne 0 ]; then
		aoeexit 1 "empty password"
	fi

	if ! tar xf ".$DEC" &> /dev/null; then
		mv ".$DEC" "$DEC"
	else
		rm ".$DEC"
	fi
	rm -f ".$DEC.old"
}

aoexit() {
	if [ -n "$1" ]; then
		printf "%s\n" "$1"
	fi
	exit 0
}

aoeexit() {
	if [ -n "$2" ]; then
		>&2 printf "ao: %s\n" "$2"
	fi
	exit $1
}

ao "$@"
