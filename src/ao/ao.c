/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <ao/ao.h>
#include <stdlib.h>

static __thread ao_t _ao;

extern __thread aovenv_t _aovenv;
extern __thread aovenv_t _assertenv;

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

aop_t ao_aovhdlr(aov_t aov, ao_t *ao)
{
	const char *aovmsg;
/* no need to check for AOINC while skipping or violating assertion */
	switch(aov) {
	case AOV_MEMV:
		aovmsg = AOV_MSG_MEMV;
		break;
	case AOV_PTRV:
		aovmsg = AOV_MSG_PTRV;
		break;
	case AOV_RTMV:
		aovmsg = AOV_MSG_RTMV;
		break;
	case AOV_UTMV:
		aovmsg = AOV_MSG_UTMV;
		break;
	case AOV_ETMV:
		aovmsg = AOV_MSG_ETMV;
		break;
	default:
		return ao_log(AOP_SKIP, ao);
	}
	ao_log(AOP_FAIL, ao);
	fstderr("%s%s", AOV_MSGHDR, aovmsg);
	ao->ao_stats ? (*ao->ao_stats)(ao) : ao_stats(ao);
	exit(AOP_FAIL);
}

aop_t ao_assert(const char *descr, void *data, size_t ncase, size_t casesz,
	aop_t (*assert_case)(void *aocase))
{
	aop_t aop = AOP_PASS;
	aov_t aov;
	_ao.logger.nlog = _ao.logger.skipped = ncase;
	_ao.logger.ndx = _ao.logger.passed = _ao.logger.failed = 0;
	if (casesz)
		_ao.aocase = (char *)data - casesz;
	else if (!(_ao.aocase = malloc((*(size_t (*)(void *))data)(NULL))))
		return AOP_SKIP;
	fstdout("%s\n", descr);
	aov_watch(AOV_MEMV);
	aov_watch(AOV_PTRV);
	aov_watch(AOV_RTMV);
	aov_watch(AOV_UTMV);
	aov_watch(AOV_ETMV);
	if (aov = aov_catch())
		aov_handle(aov, (int (*)(aov_t, void *))ao_aovhdlr, &_ao);
	if (aov_ecatch(_assertenv))
		ao_log(aop = AOP_FAIL, &_ao), ncase = 0;
	while (ncase--) {
		aop = (*assert_case)
		(
			casesz ? (_ao.aocase = (char *)_ao.aocase + casesz) : (*(void *(*)(void *))data)(_ao.aocase)
		);
		if (ao_log(aop, &_ao) == AOP_FAIL)
			break;
    }
    ao_stats(&_ao);
    if (!casesz && _ao.aocase)
        free(_ao.aocase);
	return aop;
}

void ao_nop() { }

aop_t ao_run(ao_t *ao)
{
	aop_t aop = AOP_PASS;
	size_t ncase;
	aov_t aov;
	aop_t (*aov_handler)(aov_t, ao_t *ao) = ao->aov_handler ? ao->aov_handler : ao_aovhdlr;
	void (*at_case_fail)(const void *) = ao->at_case_fail ? ao->at_case_fail : (void (*)(const void *))ao_nop;
	void (*at_case_exit)(void *) = ao->at_case_exit ? ao->at_case_exit : (void (*)(void *))ao_nop;
	int (*setup)() = ao->setup ? ao->setup : NULL;
	if (ao_setdefs(ao) != AOP_PASS)
		return AOP_SKIP;
	ncase = ao->ncase;
	if (ao->casesz)
		ao->aocase = (char *)ao->data - ao->casesz;
	else if (!(ao->aocase = malloc((*(size_t (*)(void *))ao->data)(NULL))))
		return AOP_SKIP;
	fstdout("%s\n", ao->descr);
	aov_watch(AOV_MEMV);
	aov_watch(AOV_PTRV);
	aov_watch(AOV_RTMV);
	aov_watch(AOV_UTMV);
	aov_watch(AOV_ETMV);
	if (aov = aov_catch())
		aov_handle(aov, (int (*)(aov_t, void *))aov_handler, ao);
	if (aov_ecatch(_assertenv))
		ao_log(aop = AOP_FAIL, ao), ncase = 0;
	if (setup)
		if ((*setup)())
			aop = AOP_SKIP, ncase = 0;
		else
			setup = NULL;
	while (ncase--) {
		aop = (*ao->assert_case)
		(
			ao->casesz ? (ao->aocase = (char *)ao->aocase + ao->casesz) : (*(void *(*)(void *))ao->data)(ao->aocase)
		);
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
	}
	ao->ao_stats ? (*ao->ao_stats)(ao) : ao_stats(ao);
	if (!ao->casesz && ao->aocase)
		free(ao->aocase);
	return aop;
}
