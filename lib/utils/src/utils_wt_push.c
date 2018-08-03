/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_wt_push.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include "utils.h"

char **utils_wt_push(char **wt, const char *s)
{
	size_t len = utils_wt_count(wt);
	char **new;

	new = realloc(wt, sizeof(char *) * (len + 2));
	if (!new)
		return NULL;
	new[len] = strdup(s);
	if (!new[len])
		return NULL;
	new[len + 1] = NULL;
	return new;
}