#!/bin/bash
#
#        Written by Ali Muhammed
#           uniapi@outlook.com
#              Nov 27, 2022
#

VERSION="Assert Operator 2 (debug-0.1.1)"

ao2() {
	cmd="$1"
	case "$cmd" in
	"help" )
		ao2help
		;;
	* ) ao2help
		return 1
	esac
}

ao2help() {
    printf "%s\n" "$VERSION"
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

ao2 "$@"
