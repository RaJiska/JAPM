/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: japm.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 4rth 18:54:36 2018
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "utils.h"
#include "japm.h"
#include "pbo.h"
#include "fs.h"

const arguments_t *ARGS = NULL;
const char *JAPM_PATH_FORBIDDEN_FILENAMES[] = {
	"CON", "PRN", "AUX", "NUL",
	"COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8", "COM9",
	"LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9"
};
const int JAPM_PATH_FORBIDDEN_FILENAMES_COUNT = sizeof(JAPM_PATH_FORBIDDEN_FILENAMES) / sizeof(char *);

static inline enum japm_action determine_action(const arguments_t *args)
{
	struct stat st;

	if (stat(args->input, &st) == -1)
		return FNC_PERROR_RET(enum japm_action, JAPM_ACTION_NONE, "Could not stat %s", args->input);
	if (S_ISREG(st.st_mode))
		return JAPM_ACTION_UNPACK;
	if (S_ISDIR(st.st_mode))
		return JAPM_ACTION_PACK;
	return FNC_ERROR_RET(enum japm_action, JAPM_ACTION_NONE, "Wrong file type for %s", args->input);
}

bool japm(const arguments_t *args)
{
	pbo_t pbo;
	enum japm_action action = determine_action(args);

	ARGS = args;
	switch (action)
	{
	case JAPM_ACTION_PACK:
		pbo_create(args->input, args->output);
		break;
	case JAPM_ACTION_UNPACK:
		if (!pbo_open(args->input, &pbo))
			return false;
		pbo_retrieve_entries(&pbo);
		pbo_extract(&pbo);
		pbo_close(&pbo);
		break;
	default:
		return false;
	}
	return true;
}