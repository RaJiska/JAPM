/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs_assemble_path.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 19:52:46 2018
 */

#include <string.h>
#include "fs.h"
#include "japm.h"
#include "utils.h"

char *fs_assemble_path(const char *path, const char *file, char *buf)
{
	size_t required_len = strlen(path) + strlen(file) + 2;

	if (required_len > JAPM_PATH_MAX_LENGTH)
		return FNC_ERROR_RET(char *, NULL, "Path too long '%s\\%s'", path, file);
	if (!buf) {
		if (!(buf = malloc(required_len)))
			return FNC_PERROR_RET(char *, NULL, "Could not allocate memory");
	}
	return strcat(strcat(strcpy(buf, path), "/"), file);
}