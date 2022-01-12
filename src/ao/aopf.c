/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <ao/aopf.h>

#define BOOL_FMT(b) \
	((b) ? "true" : "false")

#define _AOPF_VA \
	if (fmt && *fmt) { \
		if (*fmt != '\n' && *(fmt+1)) { \
			va_list ap; \
			va_start(ap, fmt); \
			vfstderr(fmt, ap); \
			va_end(ap); \
		} \
		fstderr("\n"); \
	} \

#define _AOPF_BOOL \
	fstderr("Expected: %s\n*Actual*: %s\n", BOOL_FMT(expected), BOOL_FMT(actual)); \
	_AOPF_VA \

#define _AOPF_SP(sp) \
    fstderr("Expected: "sp"\n*Actual*: "sp"\n", expected, actual); \
	_AOPF_VA \

#define _AOPF_FP_SP(sp) \
	fstderr("Expected: "sp"  "AOPF_FP_EXTRA_SP"\n", expected, expected); \
	fstderr("*Actual*: "sp"  "AOPF_FP_EXTRA_SP"\n", actual, actual); \
	_AOPF_VA \

#define _AOPF_PTR \
	fstderr("Expected: "); \
	if (expected) fstderr(AOPF_PTR_SP"\n", expected); \
	else fstderr("NULL\n"); \
	fstderr("*Actual*: "); \
	if (actual) fstderr(AOPF_PTR_SP"\n", actual); \
	else fstderr("NULL\n"); \
	_AOPF_VA \

#define _AOPF_STR \
	fstderr("Expected: "); \
	if (expected) fstderr(AOPF_STR_SP"\n", expected); \
	else fstderr("NULL\n"); \
	fstderr("*Actual*: "); \
	if (actual) fstderr(AOPF_STR_SP"\n", actual); \
	else fstderr("NULL\n"); \
	_AOPF_VA \

#define _AOPF_MEM { \
	size_t n, j; \
	fstderr("[Block #%zu]\n", nb); \
	for (n = 0; n < blksz; n += j) { \
		fstderr("0x%08X\n  expected:", n); \
		for (j = 0; n + j < blksz && j < AOPF_MEM_LINE_SZ; ++j) \
			fstderr(" "AOPF_MEM_SP, *((unsigned char *)expected+i+j+n)); \
		fstderr("\n  *actual*:"); \
		for (j = 0; n + j < blksz && j < AOPF_MEM_LINE_SZ; ++j) \
			fstderr(" "AOPF_MEM_SP, *((unsigned char *)actual+i+j+n)); \
		fstderr("\n"); \
	} \
	_AOPF_VA \
} \

#define _ASCII(ascii) \
	if ((ascii) == '\'' || (ascii) == '\\') \
		fstderr("\\%c", (ascii)); \
	else if ((ascii) >= ' ' && (ascii) <= '~') \
		fstderr("%c", (ascii)); \
	else if ((ascii) >= '\a' && (ascii) <= '\r') \
		fstderr("\\%c", esctab[(ascii) - '\a']); \
	else \
		fstderr("\\%03o", (unsigned char)(ascii)); \
/*
	   0 '\000'     6 '\006'
	   7 '\a'       8 '\b'      9 '\t'    10 '\n'    11 '\v'    12 '\f'    13 '\r'
	  14 '\016'    31 '\037'
	  32 ' '
	  39 '\''
	  92 '\\'
	 126 '~'
	 127 '\177'
	-128 '\200'    -1 '\377'
*/

#define _AOPF_ASCII_SP(sp) \
	fstderr("Expected: "sp"  \'", expected); \
	_ASCII(expected); \
	fstderr("\'\n*Actual*: "sp"  \'", actual); \
	_ASCII(actual); \
	fstderr("\'\n"); \
	_AOPF_VA \

static char esctab[] = { 'a', 'b', 't', 'n', 'v', 'f', 'r' };

aop_t aopf_expr(bool actual, const char *fmt, ...)
{
	if (actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	fstderr("Expected: true\n*Actual*: %s\n", BOOL_FMT(actual));
	_AOPF_VA;
	return AOP_FAIL;
}

aop_t aopf_bool_eq(bool expected, bool actual, const char *fmt, ...)
{
	if (expected && actual || expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_BOOL;
	return AOP_FAIL;
}

aop_t aopf_char_eq(char expected, char actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_ASCII_SP(AOPF_CHAR_SP);
	return AOP_FAIL;
}

aop_t aopf_shrt_eq(short expected, short actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_SHRT_SP);
	return AOP_FAIL;
}

aop_t aopf_int_eq(int expected, int actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_INT_SP);
	return AOP_FAIL;
}

aop_t aopf_long_eq(long expected, long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_LONG_SP);
	return AOP_FAIL;
}

aop_t aopf_llong_eq(long long expected, long long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_LLONG_SP);
	return AOP_FAIL;
}

aop_t aopf_uchar_eq(unsigned char expected, unsigned char actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_ASCII_SP(AOPF_UCHAR_SP);
	return AOP_FAIL;
}

aop_t aopf_ushrt_eq(unsigned short expected, unsigned short actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_USHRT_SP);
	return AOP_FAIL;
}

aop_t aopf_uint_eq(unsigned expected, unsigned actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_UINT_SP);
	return AOP_FAIL;
}

aop_t aopf_ulong_eq(unsigned long expected, unsigned long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_ULONG_SP);
	return AOP_FAIL;
}

aop_t aopf_ullong_eq(unsigned long long expected, unsigned long long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_ULLONG_SP);
	return AOP_FAIL;
}

aop_t aopf_size_eq(size_t expected, size_t actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_SIZE_SP);
	return AOP_FAIL;
}

aop_t aopf_flt_eq(float expected, float actual, float reltol, float abstol, const char *fmt, ...)
{
	aop_t aop = aop_flt_eq(expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_FP_SP(AOPF_FLT_SP);
	return AOP_FAIL;
}

aop_t aopf_dbl_eq(double expected, double actual, double reltol, double abstol, const char *fmt, ...)
{
	aop_t aop = aop_dbl_eq(expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_FP_SP(AOPF_DBL_SP);
	return AOP_FAIL;
}

aop_t aopf_ldbl_eq(long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...)
{
	aop_t aop = aop_ldbl_eq(expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_FP_SP(AOPF_LDBL_SP);
	return AOP_FAIL;
}

aop_t aopf_ptr_eq(const void *expected, const void *actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_PTR;
	return AOP_FAIL;
}

aop_t aopf_str_eq(const char *expected, const char *actual, const char *fmt, ...)
{
	aop_t aop = aop_str_eq(expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_STR;
	return AOP_FAIL;
}

aop_t aopf_mem_eq(const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...)
{
    size_t nb, i;
    if (!expected || !actual) {
        if (expected == actual)
			return AOP_PASS;
		fstderr(AOPF_MSGHDR_FAIL);
		_AOPF_PTR;
		return AOP_FAIL;
	}
    for (nb = i = 0; nb < nblk; ++nb, i += blksz) {
        if (memcmp((char *)expected+i, (char *)actual+i, blksz)) {
			fstderr(AOPF_MSGHDR_FAIL);
			_AOPF_MEM;
            return AOP_FAIL;
		}
	}
    return AOP_PASS;
}

aop_t aopf_exprskp(bool actual, const char *fmt, ...)
{
	if (actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	fstderr("Expected: true\n*Actual*: %s\n", BOOL_FMT(actual));
	_AOPF_VA;
	return AOP_SKIP;
}

aop_t aopf_bool_eqskp(bool expected, bool actual, const char *fmt, ...)
{
	if (expected && actual || expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_BOOL;
	return AOP_SKIP;
}

aop_t aopf_char_eqskp(char expected, char actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_ASCII_SP(AOPF_CHAR_SP);
	return AOP_SKIP;
}

aop_t aopf_shrt_eqskp(short expected, short actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	_AOPF_SP(AOPF_SHRT_SP);
	return AOP_SKIP;
}

aop_t aopf_int_eqskp(int expected, int actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_INT_SP);
	return AOP_SKIP;
}

aop_t aopf_long_eqskp(long expected, long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_LONG_SP);
	return AOP_SKIP;
}

aop_t aopf_llong_eqskp(long long expected, long long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_LLONG_SP);
	return AOP_SKIP;
}

aop_t aopf_uchar_eqskp(unsigned char expected, unsigned char actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_ASCII_SP(AOPF_UCHAR_SP);
	return AOP_SKIP;
}

aop_t aopf_ushrt_eqskp(unsigned short expected, unsigned short actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_USHRT_SP);
	return AOP_SKIP;
}

aop_t aopf_uint_eqskp(unsigned expected, unsigned actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_UINT_SP);
	return AOP_SKIP;
}

aop_t aopf_ulong_eqskp(unsigned long expected, unsigned long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_ULONG_SP);
	return AOP_SKIP;
}

aop_t aopf_ullong_eqskp(unsigned long long expected, unsigned long long actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_ULLONG_SP);
	return AOP_SKIP;
}

aop_t aopf_size_eqskp(size_t expected, size_t actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_SIZE_SP);
	return AOP_SKIP;
}

aop_t aopf_flt_eqskp(float expected, float actual, float reltol, float abstol, const char *fmt, ...)
{
	aop_t aop = aop_flt_eqskp(expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_FP_SP(AOPF_FLT_SP);
	return AOP_SKIP;
}

aop_t aopf_dbl_eqskp(double expected, double actual, double reltol, double abstol, const char *fmt, ...)
{
	aop_t aop = aop_dbl_eqskp(expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_FP_SP(AOPF_DBL_SP);
	return AOP_SKIP;
}

aop_t aopf_ldbl_eqskp(long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...)
{
	aop_t aop = aop_ldbl_eqskp(expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_FP_SP(AOPF_LDBL_SP);
	return AOP_SKIP;
}

aop_t aopf_ptr_eqskp(const void *expected, const void *actual, const char *fmt, ...)
{
	if (expected == actual)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_PTR;
	return AOP_SKIP;
}

aop_t aopf_str_eqskp(const char *expected, const char *actual, const char *fmt, ...)
{
	aop_t aop = aop_str_eqskp(expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_STR;
	return AOP_SKIP;
}

aop_t aopf_mem_eqskp(const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...)
{
    size_t nb, i;
    if (!expected || !actual) {
        if (expected == actual)
			return AOP_PASS;
		fstderr(AOPF_MSGHDR_SKIP);
		_AOPF_PTR;
		return AOP_SKIP;
	}
    for (nb = i = 0; nb < nblk; ++nb, i += blksz) {
        if (memcmp((char *)expected+i, (char *)actual+i, blksz)) {
			fstderr(AOPF_MSGHDR_SKIP);
			_AOPF_MEM;
            return AOP_SKIP;
		}
	}
    return AOP_PASS;
}


aop_t aopf_char_cmp(aopcmp_t cmptyp, char expected, char actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_ASCII_SP(AOPF_CHAR_SP);
	return AOP_FAIL;
}

aop_t aopf_shrt_cmp(aopcmp_t cmptyp, short expected, short actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_SHRT_SP);
	return AOP_FAIL;
}

aop_t aopf_int_cmp(aopcmp_t cmptyp, int expected, int actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_INT_SP);
	return AOP_FAIL;
}

aop_t aopf_long_cmp(aopcmp_t cmptyp, long expected, long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_LONG_SP);
	return AOP_FAIL;
}

aop_t aopf_llong_cmp(aopcmp_t cmptyp, long long expected, long long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_LLONG_SP);
	return AOP_FAIL;
}

aop_t aopf_uchar_cmp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_ASCII_SP(AOPF_UCHAR_SP);
	return AOP_FAIL;
}

aop_t aopf_ushrt_cmp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_USHRT_SP);
	return AOP_FAIL;
}

aop_t aopf_uint_cmp(aopcmp_t cmptyp, unsigned expected, unsigned actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_UINT_SP);
	return AOP_FAIL;
}

aop_t aopf_ulong_cmp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_ULONG_SP);
	return AOP_FAIL;
}

aop_t aopf_ullong_cmp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_ULLONG_SP);
	return AOP_FAIL;
}

aop_t aopf_size_cmp(aopcmp_t cmptyp, size_t expected, size_t actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_SP(AOPF_SIZE_SP);
	return AOP_FAIL;
}

aop_t aopf_ptr_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_PTR;
	return AOP_FAIL;
}

aop_t aopf_flt_cmp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol, const char *fmt, ...)
{
	aop_t aop = aop_flt_cmp(cmptyp, expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_FP_SP(AOPF_FLT_SP);
	return AOP_FAIL;
}

aop_t aopf_dbl_cmp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol, const char *fmt, ...)
{
	aop_t aop = aop_dbl_cmp(cmptyp, expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_FP_SP(AOPF_DBL_SP);
	return AOP_FAIL;
}

aop_t aopf_ldbl_cmp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...)
{
	aop_t aop = aop_ldbl_cmp(cmptyp, expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_FP_SP(AOPF_LDBL_SP);
	return AOP_FAIL;
}

aop_t aopf_str_cmp(aopcmp_t cmptyp, const char *expected, const char *actual, const char *fmt, ...)
{
	aop_t aop = aop_str_cmp(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_FAIL);
	_AOPF_STR;
	return AOP_FAIL;
}

aop_t aopf_mem_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...)
{
    size_t nb, i;
    if (!expected || !actual) {
		aop_t aop = AOP_CMP(cmptyp, expected, actual);
		if (aop == AOP_PASS)
			return AOP_PASS;
		fstderr(AOPF_MSGHDR_FAIL);
		_AOPF_PTR;
		return AOP_FAIL;

	}
    for (nb = i = 0; nb < nblk; ++nb, i += blksz) {
        int e = memcmp((char *)expected+i, (char *)actual+i, blksz);
		if (AOP_CMP(cmptyp, e, 0)) {
			fstderr(AOPF_MSGHDR_FAIL);
			_AOPF_MEM;
            return AOP_FAIL;
		}
	}
    return AOP_PASS;
}


aop_t aopf_char_cmpskp(aopcmp_t cmptyp, char expected, char actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_ASCII_SP(AOPF_CHAR_SP);
	return AOP_SKIP;
}

aop_t aopf_shrt_cmpskp(aopcmp_t cmptyp, short expected, short actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_SHRT_SP);
	return AOP_SKIP;
}

aop_t aopf_int_cmpskp(aopcmp_t cmptyp, int expected, int actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_INT_SP);
	return AOP_SKIP;
}

aop_t aopf_long_cmpskp(aopcmp_t cmptyp, long expected, long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_LONG_SP);
	return AOP_SKIP;
}

aop_t aopf_llong_cmpskp(aopcmp_t cmptyp, long long expected, long long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_LLONG_SP);
	return AOP_SKIP;
}

aop_t aopf_uchar_cmpskp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_ASCII_SP(AOPF_UCHAR_SP);
	return AOP_SKIP;
}

aop_t aopf_ushrt_cmpskp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_USHRT_SP);
	return AOP_SKIP;
}

aop_t aopf_uint_cmpskp(aopcmp_t cmptyp, unsigned expected, unsigned actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_UINT_SP);
	return AOP_SKIP;
}

aop_t aopf_ulong_cmpskp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_ULONG_SP);
	return AOP_SKIP;
}

aop_t aopf_ullong_cmpskp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_ULLONG_SP);
	return AOP_SKIP;
}

aop_t aopf_size_cmpskp(aopcmp_t cmptyp, size_t expected, size_t actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_SP(AOPF_SIZE_SP);
	return AOP_SKIP;
}

aop_t aopf_flt_cmpskp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol, const char *fmt, ...)
{
	aop_t aop = aop_flt_cmpskp(cmptyp, expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_FP_SP(AOPF_FLT_SP);
	return AOP_SKIP;
}

aop_t aopf_dbl_cmpskp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol, const char *fmt, ...)
{
	aop_t aop = aop_dbl_cmpskp(cmptyp, expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_FP_SP(AOPF_DBL_SP);
	return AOP_SKIP;
}

aop_t aopf_ldbl_cmpskp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...)
{
	aop_t aop = aop_ldbl_cmpskp(cmptyp, expected, actual, reltol, abstol);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_FP_SP(AOPF_LDBL_SP);
	return AOP_SKIP;
}

aop_t aopf_ptr_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual, const char *fmt, ...)
{
	aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_PTR;
	return AOP_SKIP;
}

aop_t aopf_str_cmpskp(aopcmp_t cmptyp, const char *expected, const char *actual, const char *fmt, ...)
{
	aop_t aop = aop_str_cmpskp(cmptyp, expected, actual);
	if (aop == AOP_PASS)
		return AOP_PASS;
	fstderr(AOPF_MSGHDR_SKIP);
	_AOPF_STR;
	return AOP_SKIP;
}

aop_t aopf_mem_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...)
{
    size_t nb, i;
    if (!expected || !actual) {
		aop_t aop = AOP_CMPSKP(cmptyp, expected, actual);
		if (aop == AOP_PASS)
			return AOP_PASS;
		fstderr(AOPF_MSGHDR_SKIP);
		_AOPF_PTR;
		return AOP_SKIP;
	}
    for (nb = i = 0; nb < nblk; ++nb, i += blksz) {
        int e = memcmp((char *)expected+i, (char *)actual+i, blksz);
		if (AOP_CMPSKP(cmptyp, e, 0)) {
			fstderr(AOPF_MSGHDR_SKIP);
			_AOPF_MEM;
            return AOP_SKIP;
		}
	}
    return AOP_PASS;
}

#undef _AOPF_ASCII_SP
#undef _ASCII
#undef _AOPF_MEM
#undef _AOPF_STR
#undef _AOPF_PTR
#undef _AOPF_FP_SP
#undef _AOPF_SP
#undef _AOPF_BOOL
#undef _AOPF_VA
#undef BOOL_FMT
