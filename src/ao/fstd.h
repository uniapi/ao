/*
 * Copyright (c) 2022 Asserter, Org. All rights reserved.
 *         Use is subject to license terms.
 *            See LICENSE for details.
 */

#ifndef _AO_FSTD_H
#define _AO_FSTD_H

#include <stdio.h>
#include <stdarg.h>

#define fstdout(...) \
	fprintf(stdout, __VA_ARGS__)

#define fstderr(...) \
	fprintf(stderr, __VA_ARGS__)

#define vfstdout(fmt, ap) \
	vfprintf(stdout, (fmt), ap)

#define vfstderr(fmt, ap) \
	vfprintf(stderr, (fmt), ap)

#endif	/* _AO_FSTD_H */
