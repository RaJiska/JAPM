/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_strsplit.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:58:31 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

static int count_delims(const char *str, const char *delims, int max)
{
	int nb = 0;

	for (unsigned int it = 0; str[it]; ++it) {
		for (unsigned int ij = 0; delims[ij]; ++ij) {
			if (str[it] == delims[ij])
				++nb;
		}
	}
	return ((max > 0 && nb > max) ? max : nb);
}

static char **perror_ret_null(const char *s, void *to_free)
{
	free(to_free);
	perror(s);
	return NULL;
}

static void free_in_reverse(char **wt, int it)
{
	for (; it >= 0; --it)
		free(wt[it]);
	free(wt);
}

static int fill_elements(
	char *token,
	char **wt,
	int delims_nb,
	const char *delims)
{
	char *end = token;
	char *bak = token;
	int it = 0;

	for (; token && it <= delims_nb; ++it)
	{
		if ((it + 1) <= delims_nb)
			wt[it] = strdup(strsep(&end, delims));
		else
			wt[it] = strdup(end);
		if (!wt[it])
		{
			perror("strdup");
			free_in_reverse(wt, it);
			free(bak);
			return -1;
		}
		token = end;
	}
	free(bak);
	return it;
}

char **utils_strsplit(const char *str, const char *delims, int max_delims)
{
	int delims_nb = count_delims(str, delims, max_delims);
	char **wt = malloc(sizeof(char *) * (delims_nb + 2));
	char *token = strdup(str);
	int elems;

	if (!wt || !token)
		return perror_ret_null("alloc", token);
	elems = fill_elements(token, wt, delims_nb, delims);
	if (elems == (-1))
		return NULL;
	wt[elems] = NULL;
	return wt;
}