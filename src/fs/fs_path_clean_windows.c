/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs_path_clean.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 17:33:33 2018
 */

#include <string.h>
#include "fs.h"
#include "utils.h"

char *fs_path_clean_windows(char *path)
{
	char *found;

	while (strstr(path, "\\\\"))
		while (utils_strreplace(path, "\\\\", "\\"));
	if (*((found = strrchr(path, '\\')) + 1) == 0)
		*found = 0;
	return path;
}