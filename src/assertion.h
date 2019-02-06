/*
 * Copyright (c) 2019 Asserter. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _ASSERTION_H
#define _ASSERTION_H

#include <asserter.h>
#include <string.h>
#include <math.h>

extern assertop assert_expr(bool);
extern assertop assert_char_eq(char, char);
extern assertop assert_shrt_eq(short, short);
extern assertop assert_int_eq(int, int);
extern assertop assert_long_eq(long, long);
extern assertop assert_llong_eq(long long, long long);
extern assertop assert_uchar_eq(unsigned char, unsigned char);
extern assertop assert_ushrt_eq(unsigned short, unsigned short);
extern assertop assert_uint_eq(unsigned, unsigned);
extern assertop assert_ulong_eq(unsigned long, unsigned long);
extern assertop assert_ullong_eq(unsigned long long, unsigned long long);
extern assertop assert_flt_eq(float, float, float, float);
extern assertop assert_dbl_eq(double, double, double, double);
extern assertop assert_str_eq(const char *, const char *);
extern assertop assert_mem_eq(const void *, const void *, size_t, size_t);
extern assertop assert_list_eq(const void *, const void *,
	int (*)(const void *, const void *), void *(*)(const void *));

extern assertop assert_expr_skip(bool);
extern assertop assert_char_skip_eq(char, char);
extern assertop assert_shrt_skip_eq(short, short);
extern assertop assert_int_skip_eq(int, int);
extern assertop assert_long_skip_eq(long, long);
extern assertop assert_llong_skip_eq(long long, long long);
extern assertop assert_uchar_skip_eq(unsigned char, unsigned char);
extern assertop assert_ushrt_skip_eq(unsigned short, unsigned short);
extern assertop assert_uint_skip_eq(unsigned, unsigned);
extern assertop assert_ulong_skip_eq(unsigned long, unsigned long);
extern assertop assert_ullong_skip_eq(unsigned long long, unsigned long long);
extern assertop assert_flt_skip_eq(float, float, float, float);
extern assertop assert_dbl_skip_eq(double, double, double, double);
extern assertop assert_str_skip_eq(const char *, const char *);
extern assertop assert_mem_skip_eq(const void *, const void *, size_t, size_t);
extern assertop assert_list_skip_eq(const void *, const void *,
	int (*)(const void *, const void *), void *(*)(const void *));

/***** Thread-Safe *****/

extern assertop assert_expr_r(asserter *, bool);
extern assertop assert_char_eq_r(asserter *, char, char);
extern assertop assert_shrt_eq_r(asserter *, short, short);
extern assertop assert_int_eq_r(asserter *, int, int);
extern assertop assert_long_eq_r(asserter *, long, long);
extern assertop assert_llong_eq_r(asserter *, long long, long long);
extern assertop assert_uchar_eq_r(asserter *, unsigned char, unsigned char);
extern assertop assert_ushrt_eq_r(asserter *, unsigned short, unsigned short);
extern assertop assert_uint_eq_r(asserter *, unsigned, unsigned);
extern assertop assert_ulong_eq_r(asserter *, unsigned long, unsigned long);
extern assertop assert_ullong_eq_r(asserter *, unsigned long long, unsigned long long);
extern assertop assert_flt_eq_r(asserter *, float, float, float, float);
extern assertop assert_dbl_eq_r(asserter *, double, double, double, double);
extern assertop assert_str_eq_r(asserter *, const char *, const char *);
extern assertop assert_mem_eq_r(asserter *, const void *, const void *, size_t, size_t);
extern assertop assert_list_eq_r(asserter *, const void *, const void *,
	int (*)(const void *, const void *), void *(*)(const void *));

extern assertop assert_expr_skip_r(asserter *, bool);
extern assertop assert_char_skip_eq_r(asserter *, char, char);
extern assertop assert_shrt_skip_eq_r(asserter *, short, short);
extern assertop assert_int_skip_eq_r(asserter *, int, int);
extern assertop assert_long_skip_eq_r(asserter *, long, long);
extern assertop assert_llong_skip_eq_r(asserter *, long long, long long);
extern assertop assert_uchar_skip_eq_r(asserter *, unsigned char, unsigned char);
extern assertop assert_ushrt_skip_eq_r(asserter *, unsigned short, unsigned short);
extern assertop assert_uint_skip_eq_r(asserter *, unsigned, unsigned);
extern assertop assert_ulong_skip_eq_r(asserter *, unsigned long, unsigned long);
extern assertop assert_ullong_skip_eq_r(asserter *, unsigned long long, unsigned long long);
extern assertop assert_flt_skip_eq_r(asserter *, float, float, float, float);
extern assertop assert_dbl_skip_eq_r(asserter *, double, double, double, double);
extern assertop assert_str_skip_eq_r(asserter *, const char *, const char *);
extern assertop assert_mem_skip_eq_r(asserter *, const void *, const void *, size_t, size_t);
extern assertop assert_list_skip_eq_r(asserter *, const void *, const void *,
	int (*)(const void *, const void *), void *(*)(const void *));

#endif 	/*_ASSERTION_H */
