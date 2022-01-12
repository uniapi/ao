/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _AO_AOPF_H
#define _AO_AOPF_H

#include <ao/aop.h>
#include <ao/fstd.h>

#define AOPF_CHAR_SP		"%4d"
#define AOPF_SHRT_SP		"%hd"
#define AOPF_INT_SP			"%d"
#define AOPF_LONG_SP		"%ld"
#define AOPF_LLONG_SP		"%lld"

#define AOPF_UCHAR_SP		"%3u"
#define AOPF_USHRT_SP		"%hu"
#define AOPF_UINT_SP		"%u"
#define AOPF_ULONG_SP		"%lu"
#define AOPF_ULLONG_SP		"%llu"

#define AOPF_SIZE_SP		"zu"

#define AOPF_FLT_SP			"%.9lf"
#define AOPF_DBL_SP			"%.17lf"
#define AOPF_LDBL_SP		"%.21Lf"
#define AOPF_FP_EXTRA_SP	"%a"

#define AOPF_PTR_SP			"%p"
#define AOPF_STR_SP			"\"%s\""
#define AOPF_MEM_SP			"%02X"
#define AOPF_MEM_LINE_SZ	16

#define AOPF_MSGHDR_FAIL	"> Assertion Failed <\n"
#define AOPF_MSGHDR_SKIP	"> Assertion Skipped <\n"

#ifdef __cplusplus
extern "c" {
#endif

aop_t aopf_expr(bool actual, const char *fmt, ...);
aop_t aopf_bool_eq(bool expected, bool actual, const char *fmt, ...);

aop_t aopf_char_eq(char expected, char actual, const char *fmt, ...);
aop_t aopf_shrt_eq(short expected, short actual, const char *fmt, ...);
aop_t aopf_int_eq(int expected, int actual, const char *fmt, ...);
aop_t aopf_long_eq(long expected, long actual, const char *fmt, ...);
aop_t aopf_llong_eq(long long expected, long long actual, const char *fmt, ...);

aop_t aopf_uchar_eq(unsigned char expected, unsigned char actual, const char *fmt, ...);
aop_t aopf_ushrt_eq(unsigned short expected, unsigned short actual, const char *fmt, ...);
aop_t aopf_uint_eq(unsigned expected, unsigned actual, const char *fmt, ...);
aop_t aopf_ulong_eq(unsigned long expected, unsigned long actual, const char *fmt, ...);
aop_t aopf_ullong_eq(unsigned long long expected, unsigned long long actual, const char *fmt, ...);

aop_t aopf_size_eq(size_t expected, size_t actual, const char *fmt, ...);

aop_t aopf_flt_eq(float expected, float actual, float reltol, float abstol, const char *fmt, ...);
aop_t aopf_dbl_eq(double expected, double actual, double reltol, double abstol, const char *fmt, ...);
aop_t aopf_ldbl_eq(long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...);

aop_t aopf_ptr_eq(const void *expected, const void *actual, const char *fmt, ...);
aop_t aopf_str_eq(const char *expected, const char *actual, const char *fmt, ...);
aop_t aopf_mem_eq(const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...);


aop_t aopf_exprskp(bool actual, const char *fmt, ...);
aop_t aopf_bool_eqskp(bool expected, bool actual, const char *fmt, ...);

aop_t aopf_char_eqskp(char expected, char actual, const char *fmt, ...);
aop_t aopf_shrt_eqskp(short expected, short actual, const char *fmt, ...);
aop_t aopf_int_eqskp(int expected, int actual, const char *fmt, ...);
aop_t aopf_long_eqskp(long expected, long actual, const char *fmt, ...);
aop_t aopf_llong_eqskp(long long expected, long long actual, const char *fmt, ...);

aop_t aopf_uchar_eqskp(unsigned char expected, unsigned char actual, const char *fmt, ...);
aop_t aopf_ushrt_eqskp(unsigned short expected, unsigned short actual, const char *fmt, ...);
aop_t aopf_uint_eqskp(unsigned expected, unsigned actual, const char *fmt, ...);
aop_t aopf_ulong_eqskp(unsigned long expected, unsigned long actual, const char *fmt, ...);
aop_t aopf_ullong_eqskp(unsigned long long expected, unsigned long long actual, const char *fmt, ...);

aop_t aopf_size_eqskp(size_t expected, size_t actual, const char *fmt, ...);

aop_t aopf_flt_eqskp(float expected, float actual, float reltol, float abstol, const char *fmt, ...);
aop_t aopf_dbl_eqskp(double expected, double actual, double reltol, double abstol, const char *fmt, ...);
aop_t aopf_ldbl_eqskp(long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...);

aop_t aopf_ptr_eq(const void *expected, const void *actual, const char *fmt, ...);
aop_t aopf_str_eqskp(const char *expected, const char *actual, const char *fmt, ...);
aop_t aopf_mem_eqskp(const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...);


aop_t aopf_char_cmp(aopcmp_t cmptyp, char expected, char actual, const char *fmt, ...);
aop_t aopf_shrt_cmp(aopcmp_t cmptyp, short expected, short actual, const char *fmt, ...);
aop_t aopf_int_cmp(aopcmp_t cmptyp, int expected, int actual, const char *fmt, ...);
aop_t aopf_long_cmp(aopcmp_t cmptyp, long expected, long actual, const char *fmt, ...);
aop_t aopf_llong_cmp(aopcmp_t cmptyp, long long expected, long long actual, const char *fmt, ...);

aop_t aopf_uchar_cmp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual, const char *fmt, ...);
aop_t aopf_ushrt_cmp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual, const char *fmt, ...);
aop_t aopf_uint_cmp(aopcmp_t cmptyp, unsigned expected, unsigned actual, const char *fmt, ...);
aop_t aopf_ulong_cmp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual, const char *fmt, ...);
aop_t aopf_ullong_cmp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual, const char *fmt, ...);

aop_t aopf_size_cmp(aopcmp_t cmptyp, size_t expected, size_t actual, const char *fmt, ...);

aop_t aopf_flt_cmp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol, const char *fmt, ...);
aop_t aopf_dbl_cmp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol, const char *fmt, ...);
aop_t aopf_ldbl_cmp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...);

aop_t aopf_ptr_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, const char *fmt, ...);
aop_t aopf_str_cmp(aopcmp_t cmptyp, const char *expected, const char *actual, const char *fmt, ...);
aop_t aopf_mem_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...);


aop_t aopf_char_cmpskp(aopcmp_t cmptyp, char expected, char actual, const char *fmt, ...);
aop_t aopf_shrt_cmpskp(aopcmp_t cmptyp, short expected, short actual, const char *fmt, ...);
aop_t aopf_int_cmpskp(aopcmp_t cmptyp, int expected, int actual, const char *fmt, ...);
aop_t aopf_long_cmpskp(aopcmp_t cmptyp, long expected, long actual, const char *fmt, ...);
aop_t aopf_llong_cmpskp(aopcmp_t cmptyp, long long expected, long long actual, const char *fmt, ...);

aop_t aopf_uchar_cmpskp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual, const char *fmt, ...);
aop_t aopf_ushrt_cmpskp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual, const char *fmt, ...);
aop_t aopf_uint_cmpskp(aopcmp_t cmptyp, unsigned expected, unsigned actual, const char *fmt, ...);
aop_t aopf_ulong_cmpskp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual, const char *fmt, ...);
aop_t aopf_ullong_cmpskp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual, const char *fmt, ...);

aop_t aopf_size_cmpskp(aopcmp_t cmptyp, size_t expected, size_t actual, const char *fmt, ...);

aop_t aopf_flt_cmpskp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol, const char *fmt, ...);
aop_t aopf_dbl_cmpskp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol, const char *fmt, ...);
aop_t aopf_ldbl_cmpskp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...);

aop_t aopf_ptr_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual, const char *fmt, ...);
aop_t aopf_str_cmpskp(aopcmp_t cmptyp, const char *expected, const char *actual, const char *fmt, ...);
aop_t aopf_mem_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif	/* _AO_AOPF_H */
