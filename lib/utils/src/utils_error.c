/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_error.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Jul 5 15:12:26 2018
 */

#include "utils.h"

inline long long int utils_error(
	const char *s,
	const char *file,
	int line,
	int ret)
{
	fprintf(stderr, "%s:%d: ERROR: %s\n", file, line, s);
	return ret;
}