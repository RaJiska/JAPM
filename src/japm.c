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
#include "pbo.h"

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

	switch (action)
	{
	case JAPM_ACTION_PACK:
		break;
	case JAPM_ACTION_UNPACK:
		if (!pbo_open(args->input, &pbo))
			return false;
		pbo_retrieve_entries(&pbo);
		break;
	default:
		return false;
	}
	pbo_close(&pbo);
	return true;
}