/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _AO_ASSERT_H
#define _AO_ASSERT_H

#include <ao/aop.h>
#include <ao/fstd.h>
#include <ao/aov.h>

extern __thread aovenv_t _assertenv;

#ifdef __cplusplus
extern "c" {
#endif

aop_t assert_expr(bool actual, const char *fmt, ...);
aop_t assert_bool_eq(bool expected, bool actual, const char *fmt, ...);

aop_t assert_char_eq(char expected, char actual, const char *fmt, ...);
aop_t assert_shrt_eq(short expected, short actual, const char *fmt, ...);
aop_t assert_int_eq(int expected, int actual, const char *fmt, ...);
aop_t assert_long_eq(long expected, long actual, const char *fmt, ...);
aop_t assert_llong_eq(long long expected, long long actual, const char *fmt, ...);

aop_t assert_uchar_eq(unsigned char expected, unsigned char actual, const char *fmt, ...);
aop_t assert_ushrt_eq(unsigned short expected, unsigned short actual, const char *fmt, ...);
aop_t assert_uint_eq(unsigned expected, unsigned actual, const char *fmt, ...);
aop_t assert_ulong_eq(unsigned long expected, unsigned long actual, const char *fmt, ...);
aop_t assert_ullong_eq(unsigned long long expected, unsigned long long actual, const char *fmt, ...);

aop_t assert_size_eq(size_t expected, size_t actual, const char *fmt, ...);

aop_t assert_flt_eq(float expected, float actual, float reltol, float abstol, const char *fmt, ...);
aop_t assert_dbl_eq(double expected, double actual, double reltol, double abstol, const char *fmt, ...);
aop_t assert_ldbl_eq(long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...);

aop_t assert_ptr_eq(const void *expected, const void *actual, const char *fmt, ...);
aop_t assert_str_eq(const char *expected, const char *actual, const char *fmt, ...);
aop_t assert_mem_eq(const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...);
aop_t assert_list_eq(const void *expected, const void *actual,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *), const char *fmt, ...);


aop_t assert_char_cmp(aopcmp_t cmptyp, char expected, char actual, const char *fmt, ...);
aop_t assert_shrt_cmp(aopcmp_t cmptyp, short expected, short actual, const char *fmt, ...);
aop_t assert_int_cmp(aopcmp_t cmptyp, int expected, int actual, const char *fmt, ...);
aop_t assert_long_cmp(aopcmp_t cmptyp, long expected, long actual, const char *fmt, ...);
aop_t assert_llong_cmp(aopcmp_t cmptyp, long long expected, long long actual, const char *fmt, ...);

aop_t assert_uchar_cmp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual, const char *fmt, ...);
aop_t assert_ushrt_cmp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual, const char *fmt, ...);
aop_t assert_uint_cmp(aopcmp_t cmptyp, unsigned expected, unsigned actual, const char *fmt, ...);
aop_t assert_ulong_cmp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual, const char *fmt, ...);
aop_t assert_ullong_cmp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual, const char *fmt, ...);

aop_t assert_size_cmp(aopcmp_t cmptyp, size_t expected, size_t actual, const char *fmt, ...);

aop_t assert_flt_cmp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol, const char *fmt, ...);
aop_t assert_dbl_cmp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol, const char *fmt, ...);
aop_t assert_ldbl_cmp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol, const char *fmt, ...);

aop_t assert_ptr_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, const char *fmt, ...);
aop_t assert_str_cmp(aopcmp_t cmptyp, const char *expected, const char *actual, const char *fmt, ...);
aop_t assert_mem_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz, const char *fmt, ...);
aop_t assert_list_cmp(aopcmp_t cmptyp, const void *expected, const void *actual,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *), const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif	/* _AO_ASSERT_H */
