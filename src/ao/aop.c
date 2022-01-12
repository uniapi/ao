/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <ao/aop.h>

aop_t aop_cat(aop_t aop1, aop_t aop2)
{
	return AOP_CAT(aop1, aop2);
}

aop_t aop_expr(bool actual)
{
	return actual ? AOP_PASS : AOP_FAIL;
}

aop_t aop_bool_eq(bool expected, bool actual)
{
	return (expected && actual || expected == actual ? AOP_PASS : AOP_FAIL);
}

aop_t aop_char_eq(char expected, char actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_shrt_eq(short expected, short actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_int_eq(int expected, int actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_long_eq(long expected, long actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_llong_eq(long long expected, long long actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_uchar_eq(unsigned char expected, unsigned char actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_ushrt_eq(unsigned short expected, unsigned short actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_uint_eq(unsigned expected, unsigned actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_ulong_eq(unsigned long expected, unsigned long actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_ullong_eq(unsigned long long expected, unsigned long long actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_size_eq(size_t expected, size_t actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_flt_eq(float expected, float actual, float reltol, float abstol)
{
	float tol;
	if (expected == actual)
		return AOP_PASS;
	tol = (fabsf(expected) > fabsf(actual) ? fabsf(expected) : fabsf(actual)) * reltol;
	if (abstol > tol)
		tol = abstol;
	return fabsf(expected - actual) < tol ? AOP_PASS : AOP_FAIL;
}

aop_t aop_dbl_eq(double expected, double actual, double reltol, double abstol)
{
	double tol;
	if (expected == actual)
		return AOP_PASS;
	tol = (fabs(expected) > fabs(actual) ? fabs(expected) : fabs(actual)) * reltol;
	if (abstol > tol)
		tol = abstol;
	return fabs(expected - actual) < tol ? AOP_PASS : AOP_FAIL;
}

aop_t aop_ldbl_eq(long double expected, long double actual, long double reltol, long double abstol)
{
	long double tol;
	if (expected == actual)
		return AOP_PASS;
	tol = (fabsl(expected) > fabsl(actual) ? fabsl(expected) : fabsl(actual)) * reltol;
	if (abstol > tol)
		tol = abstol;
	return fabsl(expected - actual) < tol ? AOP_PASS : AOP_FAIL;
}

aop_t aop_ptr_eq(const void *expected, const void *actual)
{
	return AOP_EQ(expected, actual);
}

aop_t aop_str_eq(const char *expected, const char *actual)
{
	if (!expected || !actual)
		return AOP_EQ(expected, actual);
	else if (strcmp(expected, actual))
		return AOP_FAIL;
	return AOP_PASS;
}

aop_t aop_mem_eq(const void *expected, const void *actual, size_t nblk, size_t blksz)
{
	size_t i;
	if (!expected || !actual)
		return AOP_EQ(expected, actual);
	for (i = 0; nblk--; i += blksz)
		if (memcmp((char *)expected+i, (char *)actual+i, blksz))
			return AOP_FAIL;
	return AOP_PASS;
}

aop_t aop_list_eq(const void *expected, const void *actual,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (expected && actual) {
		if (cmp(expected, actual))
			return AOP_FAIL;
		expected = nxt(expected);
		actual = nxt(actual);
	}
	return expected == actual ? AOP_PASS : AOP_FAIL;
}


aop_t aop_exprskp(bool actual)
{
	return actual ? AOP_PASS : AOP_SKIP;
}

aop_t aop_bool_eqskp(bool expected, bool actual)
{
	return (expected && actual || expected == actual ? AOP_PASS : AOP_SKIP);
}

aop_t aop_char_eqskp(char expected, char actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_shrt_eqskp(short expected, short actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_int_eqskp(int expected, int actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_long_eqskp(long expected, long actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_llong_eqskp(long long expected, long long actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_uchar_eqskp(unsigned char expected, unsigned char actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_ushrt_eqskp(unsigned short expected, unsigned short actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_uint_eqskp(unsigned expected, unsigned actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_ulong_eqskp(unsigned long expected, unsigned long actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_ullong_eqskp(unsigned long long expected, unsigned long long actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_size_eqskp(size_t expected, size_t actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_flt_eqskp(float expected, float actual, float reltol, float abstol)
{
	float tol;
	if (expected == actual)
		return AOP_PASS;
	tol = (fabsf(expected) > fabsf(actual) ? fabsf(expected) : fabsf(actual)) * reltol;
	if (abstol > tol)
		tol = abstol;
	return fabsf(expected - actual) < tol ? AOP_PASS : AOP_SKIP;
}

aop_t aop_dbl_eqskp(double expected, double actual, double reltol, double abstol)
{
	double tol;
	if (expected == actual)
		return AOP_PASS;
	tol = (fabs(expected) > fabs(actual) ? fabs(expected) : fabs(actual)) * reltol;
	if (abstol > tol)
		tol = abstol;
	return fabs(expected - actual) < tol ? AOP_PASS : AOP_SKIP;
}

aop_t aop_ldbl_eqskp(long double expected, long double actual, long double reltol, long double abstol)
{
	long double tol;
	if (expected == actual)
		return AOP_PASS;
	tol = (fabsl(expected) > fabsl(actual) ? fabsl(expected) : fabsl(actual)) * reltol;
	if (abstol > tol)
		tol = abstol;
	return fabsl(expected - actual) < tol ? AOP_PASS : AOP_SKIP;
}

aop_t aop_ptr_eqskp(const void *expected, const void *actual)
{
	return AOP_EQSKP(expected, actual);
}

aop_t aop_str_eqskp(const char *expected, const char *actual)
{
	if (!expected || !actual)
		return AOP_EQSKP(expected, actual);
	else if (strcmp(expected, actual))
		return AOP_SKIP;
	return AOP_PASS;
}

aop_t aop_mem_eqskp(const void *expected, const void *actual, size_t nblk, size_t blksz)
{
	size_t i;
	if (!expected || !actual)
		return AOP_EQSKP(expected, actual);
	for (i = 0; nblk--; i += blksz)
		if (memcmp((char *)expected+i, (char *)actual+i, blksz))
			return AOP_SKIP;
	return AOP_PASS;
}

aop_t aop_list_eqskp(const void *expected, const void *actual,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (expected && actual) {
		if (cmp(expected, actual))
			return AOP_SKIP;
		expected = nxt(expected);
		actual = nxt(actual);
	}
	return expected == actual ? AOP_PASS : AOP_SKIP;
}


aop_t aop_char_cmp(aopcmp_t cmptyp, char expected, char actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_shrt_cmp(aopcmp_t cmptyp, short expected, short actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_int_cmp(aopcmp_t cmptyp, int expected, int actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_long_cmp(aopcmp_t cmptyp, long expected, long actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_llong_cmp(aopcmp_t cmptyp, long long expected, long long actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_uchar_cmp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_ushrt_cmp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_uint_cmp(aopcmp_t cmptyp, unsigned expected, unsigned actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_ulong_cmp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_ullong_cmp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_size_cmp(aopcmp_t cmptyp, size_t expected, size_t actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_flt_cmp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol)
{
	int e = aop_flt_eq(expected, actual, reltol, abstol) == AOP_PASS ? 0 : expected > actual ? 1 : -1;
	return AOP_CMP(cmptyp, e, 0);
}

aop_t aop_dbl_cmp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol)
{
	int e = aop_dbl_eq(expected, actual, reltol, abstol) == AOP_PASS ? 0 : expected > actual ? 1 : -1;
	return AOP_CMP(cmptyp, e, 0);
}

aop_t aop_ldbl_cmp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol)
{
	int e = aop_ldbl_eq(expected, actual, reltol, abstol) == AOP_PASS ? 0 : expected > actual ? 1 : -1;
	return AOP_CMP(cmptyp, e, 0);
}

aop_t aop_ptr_cmp(aopcmp_t cmptyp, const void *expected, const void *actual)
{
	return AOP_CMP(cmptyp, expected, actual);
}

aop_t aop_str_cmp(aopcmp_t cmptyp, const char *expected, const char *actual)
{
	char e, a;
	if (!expected || !actual)
		return AOP_CMP(cmptyp, expected, actual);
	while (1) {
		e = *expected++, a = *actual++;
		if (!e || !a)
			break;
		if (AOP_CMP(cmptyp, e, a))
			return AOP_FAIL;
	}
	return e == a ? AOP_PASS : AOP_CMP(cmptyp, e, a);
}

aop_t aop_mem_cmp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz)
{
	size_t i;
	if (!expected || !actual)
		return AOP_CMP(cmptyp, expected, actual);
	for (i = 0; nblk--; i += blksz) {
		int e = memcmp((char *)expected+i, (char *)actual+i, blksz);
		if (AOP_CMP(cmptyp, e, 0))
			return AOP_FAIL;
	}
	return AOP_PASS;
}

aop_t aop_list_cmp(aopcmp_t cmptyp, const void *expected, const void *actual,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (expected && actual) {
		int e = cmp(expected, actual);
		if (AOP_CMP(cmptyp, e, 0))
			return AOP_FAIL;
		expected = nxt(expected);
		actual = nxt(actual);
	}
	return expected == actual ? AOP_PASS : AOP_CMP(cmptyp, expected, actual);
}


aop_t aop_char_cmpskp(aopcmp_t cmptyp, char expected, char actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_shrt_cmpskp(aopcmp_t cmptyp, short expected, short actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_int_cmpskp(aopcmp_t cmptyp, int expected, int actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_long_cmpskp(aopcmp_t cmptyp, long expected, long actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_llong_cmpskp(aopcmp_t cmptyp, long long expected, long long actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_uchar_cmpskp(aopcmp_t cmptyp, unsigned char expected, unsigned char actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_ushrt_cmpskp(aopcmp_t cmptyp, unsigned short expected, unsigned short actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_uint_cmpskp(aopcmp_t cmptyp, unsigned expected, unsigned actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_ulong_cmpskp(aopcmp_t cmptyp, unsigned long expected, unsigned long actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_ullong_cmpskp(aopcmp_t cmptyp, unsigned long long expected, unsigned long long actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_size_cmpskp(aopcmp_t cmptyp, size_t expected, size_t actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_flt_cmpskp(aopcmp_t cmptyp, float expected, float actual, float reltol, float abstol)
{
	int e = aop_flt_eqskp(expected, actual, reltol, abstol) == AOP_PASS ? 0 : expected > actual ? 1 : -1;
	return AOP_CMPSKP(cmptyp, e, 0);
}

aop_t aop_dbl_cmpskp(aopcmp_t cmptyp, double expected, double actual, double reltol, double abstol)
{
	int e = aop_dbl_eqskp(expected, actual, reltol, abstol) == AOP_PASS ? 0 : expected > actual ? 1 : -1;
	return AOP_CMPSKP(cmptyp, e, 0);
}

aop_t aop_ldbl_cmpskp(aopcmp_t cmptyp, long double expected, long double actual, long double reltol, long double abstol)
{
	int e = aop_ldbl_eqskp(expected, actual, reltol, abstol) == AOP_PASS ? 0 : expected > actual ? 1 : -1;
	return AOP_CMPSKP(cmptyp, e, 0);
}

aop_t aop_ptr_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual)
{
	return AOP_CMPSKP(cmptyp, expected, actual);
}

aop_t aop_str_cmpskp(aopcmp_t cmptyp, const char *expected, const char *actual)
{
	char e, a;
	if (!expected || !actual)
		return AOP_CMPSKP(cmptyp, expected, actual);
	while (1) {
		e = *expected++, a = *actual++;
		if (!e || !a)
			break;
		else if (AOP_CMPSKP(cmptyp, e, a))
			return AOP_SKIP;
	}
	return e == a ? AOP_PASS : AOP_CMPSKP(cmptyp, e, a);
}

aop_t aop_mem_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual, size_t nblk, size_t blksz)
{
	size_t i;
	if (!expected || !actual)
		return AOP_CMPSKP(cmptyp, expected, actual);
	for (i = 0; nblk--; i += blksz) {
		int e = memcmp((char *)expected+i, (char *)actual+i, blksz);
		if (AOP_CMPSKP(cmptyp, e, 0))
			return AOP_SKIP;
	}
	return AOP_PASS;
}

aop_t aop_list_cmpskp(aopcmp_t cmptyp, const void *expected, const void *actual,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (expected && actual) {
		int e = cmp(expected, actual);
		if (AOP_CMP(cmptyp, e, 0))
			return AOP_SKIP;
		expected = nxt(expected);
		actual = nxt(actual);
	}
	return expected == actual ? AOP_PASS : AOP_CMPSKP(cmptyp, expected, actual);
}
