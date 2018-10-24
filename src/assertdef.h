/*
 * Copyright (c) 2018 Asserter. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _ASSERTDEF_H
#define _ASSERTDEF_H

/* Approach:
 *    <assertdef.h> is designed to be used as a building block
 *    withouth any external dependencies
 */

typedef enum {
	ASSERT_PASS,
	ASSERT_FAIL,
	ASSERT_SKIP
} assertop;

typedef enum _assertinc {
	ASSERT_AUTO,
	ASSERT_NONE
} assertinc;

#if !defined(_STDDEF_H) || !defined(_SIZE_T)
#define _SIZE_T
#if defined (_LP64)  || defined(_I32LPx)
typedef unsigned long size_t;
#elif defined(_WIN64)
typedef unsigned __int64 size_t;
#else
typedef unsigned int size_t;
#endif
#endif 	/* _SIZE_T */

#ifndef _BOOLDEF_H
#define _BOOLDEF_H

#if defined(__STDC__)
#if __STDC_VERSION__ - 0 > 199409L
	#include <stdbool.h>
#else
	typedef enum { false, true } bool;
#endif
#else
	typedef enum { false, true } bool;
#endif

enum { FALSE, TRUE };

#endif	/* _BOOLDEF_H */
typedef struct _assertlog {
	assertinc inc;
	size_t nlog;
	size_t ndx;
	size_t passed;
	size_t failed;
	size_t skipped;
} assertlog;

/* Note:
 *    these ones are intended to use as expressions or inline!
 *    please, use with caution!
 */

/* (assertlog size_t -> size_t) */
#define __assertlog_set__(logger, n) \
	(logger.nlog = n, logger.ndx = 0, \
	logger.passed = 0, logger.failed = 0, logger.skipped = logger.nlog)

/* (assertlog assertop -> assertop) */
#define __assertlog_log__(logger, aop) \
	((++logger.ndx > logger.nlog ? ++logger.nlog, ++logger.skipped : 0), \
	((aop) != ASSERT_SKIP ? \
		((aop) == ASSERT_PASS ? ++logger.passed : \
			(aop) == ASSERT_FAIL ? ++logger.failed : ++logger.skipped), \
		--logger.skipped : 0), \
	(aop))

/* (assertlog* size_t -> size_t) */
#define __assertlog_set(logger, n) \
	(logger->nlog = n, logger->ndx = 0, \
	logger->passed = 0, logger->failed = 0, logger->skipped = logger->nlog)

/* (assertlog* assertop -> assertop) */
#define __assertlog_log(logger, aop) \
	(!logger ? (aop) : \
		((++logger->ndx > logger->nlog ? ++logger->nlog, ++logger->skipped : 0), \
		((aop) != ASSERT_SKIP ? \
			((aop) == ASSERT_PASS ? ++logger->passed : \
				(aop) == ASSERT_FAIL ? ++logger->failed : ++logger->skipped), \
			--logger->skipped : 0), \
		(aop)))

/* (integral integral -> assertop) */
#define __assert_eq(actual, expected) \
	((actual) != (expected) ? ASSERT_FAIL : ASSERT_PASS)

/* (integral integral -> assertop) */
#define __assert_skip_eq(actual, expected) \
	((actual) != (expected) ? ASSERT_SKIP : ASSERT_PASS)

#endif 	/* _ASSERTDEF_H */
