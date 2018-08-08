/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_wt_copy.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"

static void free_all_on_error(char **new, size_t it)
{
	for (; it > 0; --it)
		free(new[it - 1]);
	free(new);
}

char **utils_wt_copy(char * const *wt)
{
	size_t len = utils_wt_count(wt);
	char **new = malloc(sizeof(char *) * (len + 1));

	if (!new)
		return NULL;
	for (size_t it = 0; it < len; ++it) {
		new[it] = malloc(sizeof(char) * (strlen(wt[it]) + 1));
		if (!new[it])
			free_all_on_error(new, it);
		strcpy(new[it], wt[it]);
	}
	new[len] = NULL;
	return new;
}