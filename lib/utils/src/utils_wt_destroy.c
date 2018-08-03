
/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_wt_destroy.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include "utils.h"

void utils_wt_destroy(char **wt)
{
	if (!wt)
		return;
	for (unsigned int it = 0; wt[it]; ++it)
		free(wt[it]);
	free(wt);
}