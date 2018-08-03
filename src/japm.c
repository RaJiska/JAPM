/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: japm.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 18:54:36 2018
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "utils.h"

#include "japm.h"

static bool stat_file(const char *file, struct stat *st)
{
	if (stat(file, st) == -1) {
		fprintf(stderr, "Could not stat %s: %s\n", file, strerror(errno));
		return false;
	}
	return true;
}

static inline enum japm_action determine_action(const arguments_t *args)
{
	struct stat st_in;
	struct stat st_out;

	if (!stat_file(args->input, &st_in) || !stat_file(args->output, &st_out))
		return JAPM_ACTION_NONE;
	if (S_ISREG(st_in.st_mode) && S_ISDIR(st_out.st_mode))
		return JAPM_ACTION_UNPACK;
	if (S_ISDIR(st_in.st_mode) && S_ISREG(st_out.st_mode))
		return JAPM_ACTION_PACK;
	return FNC_ERROR_RET("Wrong file type for either input or output",
		enum japm_action,
		JAPM_ACTION_NONE);
}

bool japm(const arguments_t *args)
{
	enum japm_action action = determine_action(args);

	if (action == JAPM_ACTION_NONE)
		return false;
	return true;
}