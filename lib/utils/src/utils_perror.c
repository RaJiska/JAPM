/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_perror.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Jul 5 14:38:27 2018
 */

#include "utils.h"

inline long long int utils_perror(
	const char *s,
	const char *file,
	int line,
	int ret)
{
	fprintf(stderr, "%s:%d: %s: %s\n", file, line, s, strerror(errno));
	return ret;
}