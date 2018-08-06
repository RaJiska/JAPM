/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs_path_is_valid.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 17:16:28 2018
 */

#include "fs.h"
#include "japm.h"
#include "utils.h"

bool fs_path_is_valid(const char *path)
{
	char **wt;
	size_t len = strlen(path);

	if (*path == '\\' || strstr(path, "..\\"))
		return false;
	for (size_t it = 0; it < len; ++it) {
		if (!isprint(path[it]))
			return false;
	}
	if (!(wt = utils_strsplit(path, "\\", 0)))
		return FNC_ERROR_RET(bool, false, "Could not allocate memory");
	for (size_t it = 0; wt[it]; ++it) {
		for (int ij = 0; ij < sizeof(JAPM_PATH_FORBIDDEN_FILENAMES) / sizeof(char *); ++ij) {
			if (!strcmp(JAPM_PATH_FORBIDDEN_FILENAMES[ij], wt[it])) {
				utils_wt_destroy(wt);
				return false;
			}
		}
		if (strpbrk(wt[it], JAPM_PATH_FORBIDDEN_CHARS) ||
			strpbrk(wt[it] + strlen(wt[it]) - 1, JAPM_PATH_FORBIDDEN_ENDCHARS)) {
				utils_wt_destroy(wt);
				return false;
			}
	}
	utils_wt_destroy(wt);
	return true;
}