/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_wt_count.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:59:33 2018
 */

#include "utils.h"

size_t utils_wt_count(char * const *wt)
{
	size_t count = 0;

	if (!wt)
		return 0;
	for (; wt[count]; ++count);
	return count;
}