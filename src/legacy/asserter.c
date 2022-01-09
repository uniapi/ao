/*
 * Copyright (c) 2018 Asserter. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <asserter.h>
#include <stdio.h>

static asserter _ar;

assertop asserter_mode_log(assertop aop)
{
	return asserter_mode_log_r(&_ar, aop);
}

assertop asserter_mode_log_r(asserter *ar, assertop aop)
{
	if (ar && ar->logger.inc == ASSERT_AUTO)
		asserter_log_r(ar, aop);
	return aop;
}

void asserter_attach(char *descr, size_t ntest, assertinc inc)
{
	asserter_attach_r(&_ar, descr, ntest, inc);
}

assertop asserter_log(assertop aop)
{
	return asserter_log_r(&_ar, aop);
}

void asserter_stats()
{
	asserter_stats_r(&_ar);
}

void asserter_set(char *descr, void *set, size_t n, size_t size, void (*setter)(void *set), assertinc inc)
{
	asserter_set_r(&_ar, descr, set, n, size, setter, inc);
}

void asserter_geset(char *descr, size_t n, size_t size, void *(*generator)(void *set), void (*setter)(void *set), assertinc inc)
{
	asserter_geset_r(&_ar, descr, n, size, generator, setter, inc);
}

void asserter_detach()
{
	/* Nothing to do here yet */
}


/***** Thread-Safe *****/

asserter *asserter_attach_r(asserter *ar, char *descr, size_t ntest, assertinc inc)
{
	if (!ar && !(ar = (asserter *)malloc(sizeof (asserter))))
		return NULL;
	ar->logger.inc = inc;
	ar->logger.nlog = ntest;
	ar->logger.ndx = 0;
	ar->logger.passed = 0;
	ar->logger.failed = 0;
	ar->logger.skipped = ntest;
	fprintf(stdout, "%s\n", descr);
	return ar;
}

assertop asserter_log_r(asserter *ar, assertop aop)
{
	if (!ar)
		return aop;
	if (ar->logger.ndx+1 > ar->logger.nlog) {
		ar->logger.nlog++;
		ar->logger.skipped++;
	}
	if (aop != ASSERT_SKIP) {
		if (aop == ASSERT_PASS)
			ar->logger.passed++;
		else if(aop == ASSERT_FAIL)
			ar->logger.failed++;
		ar->logger.skipped--;
	}
	ar->logger.ndx++;
	return aop;
}

void asserter_stats_r(const asserter *ar)
{
	fprintf(stdout, "Total Tests: %u\n", ar->logger.nlog);
	fprintf(stdout, "    Passed: %u, Failed: %u, Skipped: %u\n", ar->logger.passed, ar->logger.failed, ar->logger.skipped);
}

void asserter_set_r(asserter *ar, char *descr, void *set, size_t n, size_t size, void (*setter)(void *set), assertinc inc)
{
	size_t i;
	asserter_attach_r(ar, descr, n, inc);
	for (i=0ul; i < n; ++i) {
		(*setter)(set);
		set = (char *)set + size;
	}
	asserter_stats_r(ar);
}

void asserter_geset_r(asserter *ar, char *descr, size_t n, size_t size, void *(*generator)(void *set), void (*setter)(void *set), assertinc inc)
{
	void *set = calloc(1, sizeof size);
	if (!set)
		return;
	asserter_attach_r(ar, descr, n, inc);
	while (n--) {
		(*generator)(set);
		(*setter)(set);
	}
	free(set);
	asserter_stats_r(ar);
}

void asserter_detach_r(asserter *ar)
{
	if (ar)
		free(ar);
}
