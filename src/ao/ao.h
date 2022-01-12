/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _AO_H
#define _AO_H

#include <ao/aop.h>
#include <ao/fstd.h>

typedef struct aolog {
	size_t nlog;
	size_t ndx;
	size_t passed;
	size_t failed;
	size_t skipped;
} aolog_t;

typedef enum aoinc {
	AOINC_AUTO,
	AOINC_NONE
} aoinc_t;

typedef enum aomode {
	AOMODE_STOP,
	AOMODE_NONE
} aomode_t;

typedef struct ao {
	const char *descr;
	void *data;
	size_t ncase;
	size_t casesz;
	aop_t (*assert_case)(void *aocase);
	void (*at_case_fail)(const void *aocase);
	void (*at_case_exit)(void *aocase);
	int (*setup)();
	void (*ao_stats)(const struct ao *ao);
	aoinc_t inc;
	aomode_t mode;
	aolog_t logger;	/* Do not use it as overwritten automatically! */
	void *aocase;
} ao_t;

aop_t ao_log(aop_t aop, ao_t *ao);

aop_t ao_assert(const char *descr, void *data, size_t ncase, size_t casesz,
	aop_t (*assert_case)(void *aocase));

aop_t ao_run(ao_t *ao);

#endif 	/* _AO_H */
