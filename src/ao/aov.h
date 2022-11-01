/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _AO_AOV_H
#define _AO_AOV_H

#include <ao/aop.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

typedef enum aov {
	AOV_NONE,
	AOV_MEMV = SIGSEGV,
	AOV_PTRV = SIGUSR1,
	AOV_RTMV = SIGALRM,
	AOV_UTMV = SIGVTALRM,
	AOV_ETMV = SIGPROF
} aov_t;

#define AOV_MSGHDR		"*** Assertion Operation Violation ***\n"
#define AOV_MSG_MEMV	"Unexpected: Memory Access\n"
#define AOV_MSG_PTRV	"Unexpected: Pointer Value\n"
#define AOV_MSG_RTMV	"Unexpected: Real Time Expiration\n"
#define AOV_MSG_UTMV	"Unexpected: User Time Expiration\n"
#define AOV_MSG_ETMV	"Unexpected: Execution Time Expiration\n"

typedef jmp_buf aovenv_t;
extern __thread aovenv_t _aovenv;

#define aov_catch()			setjmp(_aovenv)
#define aov_ecatch(env)		setjmp(env)

#ifdef __cplusplus
extern "c" {
#endif

void aov_ethrow(aovenv_t env, int e);

int aov_watch(aov_t aov);
int aov_handle(aov_t aov, int (*aovhdlr)(aov_t aov, void *arg), void *arg);

aop_t aov_assert(aov_t aov, aop_t aop);
aop_t aov_assert_memv(const void *expected, const void *actual, size_t nblk, size_t blksz);
aop_t aov_assert_ptrv(const void *expected, const void *actual);

#ifdef __cplusplus
}
#endif

#endif 	/* _AO_AOV_H */
