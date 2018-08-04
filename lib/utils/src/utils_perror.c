/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_perror.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Jul 5 14:38:27 2018
 */

#include "utils.h"
#include <stdarg.h>

inline long long int utils_perror(
	long long int ret,
	const char *s,
	...)
{
	int last_errno = errno;
	va_list va;

	va_start(va, s);
	vfprintf(stderr, s, va);
	va_end(va);
	fprintf(stderr, ": %s\n", strerror(errno));
	return ret;
}