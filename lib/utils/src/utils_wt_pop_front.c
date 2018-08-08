/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_wt_pop_front.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include <stdlib.h>
#include <string.h>
#include "utils.h"

char **utils_wt_pop_front(char **wt, char **str)
{
	size_t len = utils_wt_count(wt);

	if (!wt || !wt[0] || !str)
		return NULL;
	*str = wt[0];
	wt = memmove(wt, wt + 1, sizeof(*wt) * (len - 1));
	wt[len - 1] = NULL;
	return wt;
}