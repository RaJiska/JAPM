/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs_path_get_last_link.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Wed Aug 8th 13:38:44 2018
 */

#include <string.h>
#include "japm.h"
#include "fs.h"

char *fs_path_get_last_link(char *path)
{
	char *last = strrchr(path, JAPM_PATH_SEP);

	if (!last)
		return path;
	if (!*(last + 1)) {
		for (; last != path && *last == JAPM_PATH_SEP; --last);
		for (; last != path && *(last - 1) != JAPM_PATH_SEP; --last);
	}
	return (!*(last + 1)) ? path : last;
}