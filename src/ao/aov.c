/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#include <ao/aov.h>

static void aov_report(aov_t aov);

__thread aovenv_t _aovenv;

void aov_ethrow(aovenv_t env, int e)
{
	longjmp(env, e);
	exit(e);
}

int aov_watch(aov_t aov)
{
	if (aov == AOV_NONE) {
		return
			signal(AOV_MEMV, SIG_DFL) == SIG_ERR ||
			signal(AOV_PTRV, SIG_DFL) == SIG_ERR ||
			signal(AOV_RTMV, SIG_DFL) == SIG_ERR ||
			signal(AOV_UTMV, SIG_DFL) == SIG_ERR ||
			signal(AOV_ETMV, SIG_DFL) == SIG_ERR
		;
	}
	return signal(aov, (void (*)(int))aov_report) == SIG_ERR;
}

int aov_handle(aov_t aov, int (*aovhdlr)(aov_t aov, void *arg), void *arg)
{
	return aovhdlr ? aovhdlr(aov, arg) : aov;
}


aop_t aov_assert(aov_t aov, aop_t aop)
{
	if (aop == AOP_FAIL) {
		raise(aov);
		exit(aov);
	}
	return aop;
}

aop_t aov_assert_memv(const void *expected, const void *actual, size_t nblk, size_t blksz)
{
	return aov_assert(AOV_MEMV, aop_mem_eq(expected, actual, nblk, blksz));
}

aop_t aov_assert_ptrv(const void *expected, const void *actual)
{
	return aov_assert(AOV_PTRV, aop_ptr_eq(expected, actual));
}

static void aov_report(aov_t aov)
{
	aov_watch(aov);
	aov_ethrow(_aovenv, aov);
}
