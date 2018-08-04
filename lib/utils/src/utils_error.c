/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_error.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Jul 5 15:12:26 2018
 */

#include <stdarg.h>
#include "utils.h"

inline long long int utils_error(
	long long int ret,
	const char *s,
	...)
{
	va_list va;

	va_start(va, s);
	vfprintf(stderr, s, va);
	va_end(va);
	fprintf(stderr, "\n");
	return ret;
}