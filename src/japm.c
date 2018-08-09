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

static inline char *get_pack_output_file(char *args_input, char *args_output)
{
	char *output_file;
	char *last_link;

	if (args_output)
		return args_output;
	last_link = fs_path_get_last_link(args_input);
	if (!(output_file = malloc(strlen(last_link) + 4 + 1)))
		return FNC_PERROR_RET(char *, NULL, "Could not allocate memory");
	strcpy(output_file, last_link);
	while (utils_strreplace(output_file, JAPM_PATH_SEP_STR, NULL));
	strcat(output_file, ".pbo");
	return output_file;
}

static inline char *get_unpack_output_file(char *args_input, char *args_output)
{
	char *output_file;

	if (args_output)
		return args_output;
	if (!(output_file = strdup(fs_path_get_last_link(args_input))))
		return FNC_PERROR_RET(char *, NULL, "Could not allocate memory");
	*strstr(output_file, ".pbo") = 0;
	return output_file;
}

static inline enum japm_action determine_action(const arguments_t *args)
{
	struct stat st;
	char *buf;

	if (stat(args->input, &st) == -1)
		return FNC_PERROR_RET(enum japm_action, JAPM_ACTION_NONE, "Could not stat %s", args->input);

	if (S_ISREG(st.st_mode)) {
		if ((buf = strstr(args->input, ".pbo")) && !strcmp(buf, ".pbo"))
			return JAPM_ACTION_UNPACK;
		else
			FNC_WARN("Input file (%s) does not have the .pbo extension: skipping", args->input);
	}
	if (S_ISDIR(st.st_mode))
		return JAPM_ACTION_PACK;
	return FNC_ERROR_RET(enum japm_action, JAPM_ACTION_NONE, "Wrong file type for %s", args->input);
}

bool japm(const arguments_t *args)
{
	pbo_t pbo;
	enum japm_action action = determine_action(args);
	char *output_file;

	ARGS = args;
	if (args)
	switch (action)
	{
	case JAPM_ACTION_PACK:
		if (!(output_file = get_pack_output_file(args->input, args->output)))
			return false;
		pbo_create(args->input, output_file);
		break;
	case JAPM_ACTION_UNPACK:
		if (!pbo_open(args->input, &pbo))
			return false;
		pbo_retrieve_entries(&pbo);
		if (!(output_file = get_unpack_output_file(args->input, args->output)))
			return false;
		pbo_extract(&pbo, output_file);
		pbo_close(&pbo);
		break;
	default:
		return false;
	}
	if (output_file != args->output)
		free(output_file);
	return true;
}