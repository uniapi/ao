/*
 * Copyright (c) 2019 Asserter. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <assertion.h>

assertop assert_expr(bool actual)
{
	return asserter_mode_log(__assert_eq(actual, true));
}

assertop assert_char_eq(char actual, char expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_shrt_eq(short actual, short expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_int_eq(int actual, int expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_long_eq(long actual, long expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_llong_eq(long long actual, long long expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_uchar_eq(unsigned char actual, unsigned char expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_ushrt_eq(unsigned short actual, unsigned short expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_uint_eq(unsigned actual, unsigned expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_ulong_eq(unsigned long actual, unsigned long expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_ullong_eq(unsigned long long actual, unsigned long long expected)
{
	return asserter_mode_log(__assert_eq(actual, expected));
}

assertop assert_flt_eq(float actual, float expected, float reltol, float abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	float tol;
	if (actual != expected) {
		tol = (fabsf(actual) > fabsf(expected) ? fabsf(actual) : fabsf(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabsf(actual - expected) < tol ? ASSERT_PASS : ASSERT_FAIL;
	}
	return asserter_mode_log(aop);
}

assertop assert_dbl_eq(double actual, double expected, double reltol, double abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	double tol;
	if (actual != expected) {
		tol = (fabs(actual) > fabs(expected) ? fabs(actual) : fabs(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabs(actual - expected) < tol ? ASSERT_PASS : ASSERT_FAIL;
	}
	return asserter_mode_log(aop);
}

assertop assert_str_eq(const char *actual, const char *expected)
{
	assertop aop = ASSERT_PASS;
	if (!actual || !expected) {
		if (actual != expected)
			aop = ASSERT_FAIL;
	}
	else if (strcmp(actual, expected))
		aop = ASSERT_FAIL;
	return asserter_mode_log(aop);
}

assertop assert_mem_eq(const void *actual, const void *expected, size_t n, size_t size)
{
	size_t i;
	if (!actual || !expected)
		return asserter_mode_log(__assert_eq(actual, expected));
	for (i = 0ul; n--; i += size)
		if (memcmp((char *)actual+i, (char *)expected+i, size))
			return asserter_mode_log(ASSERT_FAIL);
	return asserter_mode_log(ASSERT_PASS);
}

assertop assert_list_eq(const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (actual || expected) {
		if (cmp(actual, expected))
			return asserter_mode_log(ASSERT_FAIL);
		actual = nxt(actual);
		expected = nxt(expected);
	}
	return asserter_mode_log(ASSERT_PASS);
}

assertop assert_expr_skip(bool actual)
{
	return asserter_mode_log(__assert_skip_eq(actual, true));
}

assertop assert_char_skip_eq(char actual, char expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_shrt_skip_eq(short actual, short expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_int_skip_eq(int actual, int expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_long_skip_eq(long actual, long expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_llong_skip_eq(long long actual, long long expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_uchar_skip_eq(unsigned char actual, unsigned char expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_ushrt_skip_eq(unsigned short actual, unsigned short expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_uint_skip_eq(unsigned actual, unsigned expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_ulong_skip_eq(unsigned long actual, unsigned long expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_ullong_skip_eq(unsigned long long actual, unsigned long long expected)
{
	return asserter_mode_log(__assert_skip_eq(actual, expected));
}

assertop assert_flt_skip_eq(float actual, float expected, float reltol, float abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	float tol;
	if (actual != expected) {
		tol = (fabsf(actual) > fabsf(expected) ? fabsf(actual) : fabsf(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabsf(actual - expected) < tol ? ASSERT_PASS : ASSERT_SKIP;
	}
	return asserter_mode_log(aop);
}

assertop assert_dbl_skip_eq(double actual, double expected, double reltol, double abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	double tol;
	if (actual != expected) {
		tol = (fabs(actual) > fabs(expected) ? fabs(actual) : fabs(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabs(actual - expected) < tol ? ASSERT_PASS : ASSERT_SKIP;
	}
	return asserter_mode_log(aop);
}

assertop assert_str_skip_eq(const char *actual, const char *expected)
{
	assertop aop = ASSERT_PASS;
	if (!actual || !expected) {
		if (actual != expected)
			aop = ASSERT_SKIP;
	}
	else if (strcmp(actual, expected))
		aop = ASSERT_SKIP;
	return asserter_mode_log(aop);
}

assertop assert_mem_skip_eq(const void *actual, const void *expected, size_t n, size_t size)
{
	size_t i;
	if (!actual || !expected)
		return asserter_mode_log(__assert_eq(actual, expected));
	for (i = 0ul; n--; i += size)
		if (memcmp((char *)actual+i, (char *)expected+i, size))
			return asserter_mode_log( ASSERT_SKIP);
	return asserter_mode_log(ASSERT_PASS);
}

assertop assert_list_skip_eq(const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (actual || expected) {
		if (cmp(actual, expected))
			return asserter_mode_log(ASSERT_SKIP);
		actual = nxt(actual);
		expected = nxt(expected);
	}
	return asserter_mode_log(ASSERT_PASS);
}

/***** Thread-Safe *****/

assertop assert_expr_r(asserter *ar, bool actual)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, true));
}

assertop assert_char_eq_r(asserter *ar, char actual, char expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_shrt_eq_r(asserter *ar, short actual, short expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_int_eq_r(asserter *ar, int actual, int expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_long_eq_r(asserter *ar, long actual, long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_llong_eq_r(asserter *ar, long long actual, long long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_uchar_eq_r(asserter *ar, unsigned char actual, unsigned char expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_ushrt_eq_r(asserter *ar, unsigned short actual, unsigned short expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_uint_eq_r(asserter *ar, unsigned actual, unsigned expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_ulong_eq_r(asserter *ar, unsigned long actual, unsigned long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_ullong_eq_r(asserter *ar, unsigned long long actual, unsigned long long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_flt_eq_r(asserter *ar, float actual, float expected, float reltol, float abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	float tol;
	if (actual != expected) {
		tol = (fabsf(actual) > fabsf(expected) ? fabsf(actual) : fabsf(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabsf(actual - expected) < tol ? ASSERT_PASS : ASSERT_FAIL;
	}
	return asserter_mode_log_r(ar, aop);
}

assertop assert_dbl_eq_r(asserter *ar, double actual, double expected, double reltol, double abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	double tol;
	if (actual != expected) {
		tol = (fabs(actual) > fabs(expected) ? fabs(actual) : fabs(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabs(actual - expected) < tol ? ASSERT_PASS : ASSERT_FAIL;
	}
	return asserter_mode_log_r(ar, aop);
}

assertop assert_str_eq_r(asserter *ar, const char *actual, const char *expected)
{
	assertop aop = ASSERT_PASS;
	if (!actual || !expected) {
		if (actual != expected)
			aop = ASSERT_FAIL;
	}
	else if (strcmp(actual, expected))
		aop = ASSERT_FAIL;
	return asserter_mode_log_r(ar, aop);
}

assertop assert_mem_eq_r(asserter *ar, const void *actual, const void *expected, size_t n, size_t size)
{
	size_t i;
	if (!actual || !expected)
		return asserter_mode_log_r(ar, __assert_eq(actual, expected));
	for (i = 0u; n--; i += size)
		if (memcmp((char *)actual+i, (char *)expected+i, size))
			return asserter_mode_log_r(ar, ASSERT_FAIL);
	return asserter_mode_log_r(ar, ASSERT_PASS);
}

assertop assert_list_eq_r(asserter *ar, const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (actual || expected) {
		if (cmp(actual, expected))
			return asserter_mode_log_r(ar, ASSERT_FAIL);
		actual = nxt(actual);
		expected = nxt(expected);
	}
	return asserter_mode_log_r(ar, ASSERT_PASS);
}

assertop assert_expr_skip_r(asserter *ar, bool actual)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, true));
}

assertop assert_char_skip_eq_r(asserter *ar, char actual, char expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_shrt_skip_eq_r(asserter *ar, short actual, short expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_int_skip_eq_r(asserter *ar, int actual, int expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_long_skip_eq_r(asserter *ar, long actual, long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_llong_skip_eq_r(asserter *ar, long long actual, long long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_uchar_skip_eq_r(asserter *ar, unsigned char actual, unsigned char expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_ushrt_skip_eq_r(asserter *ar, unsigned short actual, unsigned short expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_uint_skip_eq_r(asserter *ar, unsigned actual, unsigned expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_ulong_skip_eq_r(asserter *ar, unsigned long actual, unsigned long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_ullong_skip_eq_r(asserter *ar, unsigned long long actual, unsigned long long expected)
{
	return asserter_mode_log_r(ar, __assert_eq(actual, expected));
}

assertop assert_flt_skip_eq_r(asserter *ar, float actual, float expected, float reltol, float abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	float tol;
	if (actual != expected) {
		tol = (fabsf(actual) > fabsf(expected) ? fabsf(actual) : fabsf(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabsf(actual - expected) < tol ? ASSERT_PASS : ASSERT_SKIP;
	}
	return asserter_mode_log_r(ar, aop);
}

assertop assert_dbl_skip_eq_r(asserter *ar, double actual, double expected, double reltol, double abstol)
{
	/*
	 * Do: implement NaN and Inf support!
	 */
	assertop aop = ASSERT_PASS;
	double tol;
	if (actual != expected) {
		tol = (fabs(actual) > fabs(expected) ? fabs(actual) : fabs(expected)) * reltol;
		if (abstol > tol)
			tol = abstol;
		aop = fabs(actual - expected) < tol ? ASSERT_PASS : ASSERT_SKIP;
	}
	return asserter_mode_log_r(ar, aop);
}

assertop assert_str_skip_eq_r(asserter *ar, const char *actual, const char *expected)
{
	assertop aop = ASSERT_PASS;
	if (!actual || !expected) {
		if (actual != expected)
			aop = ASSERT_SKIP;
	}
	else if (strcmp(actual, expected))
		aop = ASSERT_SKIP;
	return asserter_mode_log_r(ar, aop);
}

assertop assert_mem_skip_eq_r(asserter *ar, const void *actual, const void *expected, size_t n, size_t size)
{
	size_t i;
	if (!actual || !expected)
		return asserter_mode_log_r(ar, __assert_eq(actual, expected));
	for (i = 0ul; n--; i += size)
		if (memcmp((char *)actual+i, (char *)expected+i, size))
			return asserter_mode_log_r(ar, ASSERT_SKIP);
	return asserter_mode_log_r(ar,ASSERT_PASS);
}

assertop assert_list_skip_eq_r(asserter *ar, const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *))
{
	while (actual || expected) {
		if (cmp(actual, expected))
			return asserter_mode_log_r(ar, ASSERT_SKIP);
		actual = nxt(actual);
		expected = nxt(expected);
	}
	return asserter_mode_log_r(ar, ASSERT_PASS);
}


/*
 * Assertions using comparison modes
 */

assertop assert_flt_cmp(float actual, float expected, float reltol, float abstol, assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_dbl_cmp(double actual, double expected, double reltol, double abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_str_cmp(const char *actual, const char *expected, assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_mem_cmp(const void *actual, const void *expected, size_t n, size_t size,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_list_cmp(const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *), assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"

}

assertop assert_flt_skip_cmp(float actual, float expected, float reltol, float abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_dbl_skip_cmp(double actual, double expected, double reltol, double abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_str_skip_cmp(const char *actual, const char *expected, assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_mem_skip_cmp(const void *actual, const void *expected, size_t n, size_t size,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_list_skip_cmp(const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *), assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"

}

/***** Thread-Safe *****/

assertop assert_flt_cmp_r(asserter *ar, float actual, float expected, float reltol, float abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_dbl_cmp_r(asserter *ar, double actual, double expected, double reltol, double abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_str_cmp_r(asserter *ar, const char *actual, const char *expected, assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_mem_cmp_r(asserter *ar, const void *actual, const void *expected, size_t n, size_t size,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_list_cmp_r(asserter *ar, const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *), assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"

}

assertop assert_flt_skip_cmp_r(asserter *ar, float actual, float expected, float reltol, float abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_dbl_skip_cmp_r(asserter *ar, double actual, double expected, double reltol, double abstol,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation!"
}

assertop assert_str_skip_cmp_r(asserter *ar, const char *actual, const char *expected, assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_mem_skip_cmp_r(asserter *ar, const void *actual, const void *expected, size_t n, size_t size,
	assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"
}

assertop assert_list_skip_cmp_r(asserter *ar, const void *actual, const void *expected,
	int (*cmp)(const void *, const void *), void *(*nxt)(const void *), assertmode mode)
{
	/*
	 * Do: supply implementation!
	 */
#error "Unsupplied Implementation"

}
