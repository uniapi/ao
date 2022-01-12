/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <ao/ao.h>

static __thread ao_t _ao;

static void ao_stats(const ao_t *ao)
{
	fstdout("\nTotal Cases: %zu\n", ao->logger.nlog);
	fstdout("    Passed: %zu, Failed: %zu, Skipped: %zu\n",
		ao->logger.passed, ao->logger.failed, ao->logger.skipped);
}

static aop_t ao_setdefs(ao_t *ao)
{
	if (!ao || !ao->data || !ao->assert_case)
		return AOP_SKIP;
	if (!ao->ao_stats)
		ao->ao_stats = ao_stats;
	ao->logger.nlog = ao->logger.skipped = ao->ncase;
	ao->logger.ndx = ao->logger.passed = ao->logger.failed = 0;
	return AOP_PASS;
}

aop_t ao_log(aop_t aop, ao_t *ao)
{
	if (!ao)
		return aop;
	else if (++ao->logger.ndx > ao->logger.nlog)
		++ao->logger.nlog, ++ao->logger.skipped;
	if (aop != AOP_SKIP) {
		if (aop == AOP_PASS)
			++ao->logger.passed;
		else
			++ao->logger.failed;
		--ao->logger.skipped;
	}
	return aop;
}

aop_t ao_assert(const char *descr, void *data, size_t ncase, size_t casesz,
	aop_t (*assert_case)(void *aocase))
{
	aop_t aop = AOP_PASS;
	_ao.logger.nlog = _ao.logger.skipped = ncase;
	_ao.logger.ndx = _ao.logger.passed = _ao.logger.failed = 0;
	fstdout("%s\n", descr);
	while (ncase--) {
		aop = (*assert_case)(data);
		if (ao_log(aop, &_ao) == AOP_FAIL)
			break;
		data = (char *)data + casesz;
	}
	ao_stats(&_ao);
	return aop;
}

void ao_nop() { }

aop_t ao_run(ao_t *ao)
{
	aop_t aop = AOP_PASS;
	size_t ncase;
	void (*at_case_fail)(const void *) = ao->at_case_fail ? ao->at_case_fail : (void (*)(const void *))ao_nop;
	void (*at_case_exit)(void *) = ao->at_case_exit ? ao->at_case_exit : (void (*)(void *))ao_nop;
	if (ao_setdefs(ao) != AOP_PASS)
		return AOP_SKIP;
	ncase = ao->ncase;
	ao->aocase = ao->data;
	fstdout("%s\n", ao->descr);
	if (ao->setup)
		if ((*ao->setup)())
			aop = AOP_SKIP, ncase = 0;
	while (ncase--) {
		aop = (*ao->assert_case)(ao->aocase);
		if (ao->inc == AOINC_AUTO)
			ao_log(aop, ao);
		if (aop == AOP_FAIL) {
			(*at_case_fail)(ao->aocase);
			if (ao->mode == AOMODE_STOP) {
				(*at_case_exit)(ao->aocase);
				break;
			}
		}
		(*at_case_exit)(ao->aocase);
		ao->aocase = (char *)ao->aocase + ao->casesz;
	}
	ao->ao_stats ? (*ao->ao_stats)(ao) : ao_stats(ao);
	return aop;
}
