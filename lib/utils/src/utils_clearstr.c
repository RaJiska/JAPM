/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_clearstr.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include <string.h>
#include "utils.h"

static void memmove_null(char *dest, const char *src, size_t len)
{
	memmove(dest, src, len);
	dest[len] = 0;
}

char *utils_clearstr(char *s)
{
	size_t it;
	char *end;

	for (it = 0; s[it] && s[it] == ' '; ++it);
	if (it > 0)
		memmove_null(s, s + it, strlen(s + it));
	for (char *start = strchr(s, ' ');
		start; start = strchr(start + 1, ' '))
	{
		for (end = start; *end == ' '; ++end);
		if (!(*end))
			start[0] = 0;
		else if (end > start + 1)
			memmove_null(start + 1, end, strlen(end));
	}
	return s;
}