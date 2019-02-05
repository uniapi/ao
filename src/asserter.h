/*
 * Copyright (c) 2018 Asserter. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _ASSERTER_H
#define _ASSERTER_H

#include <assertdef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct _asserter {
	char *descr;
    /*
		Do: define stuff to keep params used in failed assertions
    */
    assertlog logger;
} asserter;

void asserter_attach(char *descr, size_t ntest, assertinc inc);
assertop asserter_log(assertop aop);
assertop asserter_mode_log(assertop aop);
void asserter_stats();
void asserter_set(char *descr, void *set, size_t n, size_t size, void (*setter)(void *set), assertinc inc);
void asserter_geset(char *descr, size_t n, size_t size, void *(generator)(void *set), void (*setter)(void *set), assertinc inc);
void asserter_detach();

/***** Thread-Safe *****/

asserter *asserter_attach_r(asserter *ar, char *descr, size_t ntest, assertinc inc);
assertop asserter_log_r(asserter *ar, assertop aop);
assertop asserter_mode_log_r(asserter *ar, assertop aop);
void asserter_stats_r(const asserter *ar);
void asserter_set_r(asserter *ar, char *descr, void *set, size_t num, size_t size, void (*setter)(void *set), assertinc inc);
void asserter_geset_r(asserter *ar, char *descr, size_t n, size_t size, void *(generator)(void *set), void (*setter)(void *set), assertinc inc);
void asserter_detach_r(asserter *ar);

#endif	/* _ASSERTER_H */
