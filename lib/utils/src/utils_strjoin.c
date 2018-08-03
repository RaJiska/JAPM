/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_strjoin.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include "utils.h"

char *utils_strjoin(char * const *wt, const char *separator)
{
	char *ret;
	size_t len = 0;
	size_t sep_len = (separator) ? strlen(separator) : 0;
	size_t wt_count = utils_wt_count(wt);

	for (size_t it = 0; wt[it]; ++it)
		len += strlen(wt[it]);
	ret = malloc(sizeof(char) * ((len + sep_len * wt_count) + 1));
	if (!ret)
		return NULL;
	ret[0] = 0;
	for (size_t it = 0; wt[it]; ++it) {
		if (it > 0 && separator)
			strcat(ret, separator);
		strcat(ret, wt[it]);
	}
	return ret;
}