/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_extract.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sun Aug 0 11:22:14 2018
 */

#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include "japm.h"
#include "pbo.h"
#include "utils.h"

static bool create_directory(const char *path)
{
	if (mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) {
		if (errno != EEXIST)
			return FNC_PERROR_RET(bool, false,
				"Could not create directory: %s", path);
	}
	return true;
}

static FILE *create_path_and_file(const char *path)
{
	FILE *f;
	char buffer[JAPM_PATH_MAX_LENGTH] = { 0 };
	char **wt = utils_strsplit(path, "\\", 0);
	int elem = 0;

	if (!wt)
		return FNC_ERROR_RET(FILE *, NULL, "Could not allocate memory");
	strcat(strcpy(&buffer[0], ARGS->output), "/");
	if (!create_directory(&buffer[0]))
		return false;
	for (; wt[elem + 1]; ++elem) {
		strcat(strcpy(&buffer[0], ARGS->output), "/");
		for (int it = 0; it <= elem; ++it)
			strcat(strcat(&buffer[0], wt[it]), "/");
		if (!create_directory(&buffer[0]))
			return false;
	}
	strcat(&buffer[0], wt[elem]);
	if ((f = fopen(&buffer[0], "w+b")) == NULL)
		return FNC_PERROR_RET(FILE *, 0, "Could not create file: %s", &buffer[0]);
	utils_wt_destroy(wt);
	return f;
}

/* TODO: Handle compression & set file last modified */
bool pbo_extract(const pbo_t *pbo)
{
	FILE *f = NULL;
	list_t *curr = pbo->entries;
	pbo_entry_t *curr_entry;
	byte_t *curr_data = pbo->map_data_block;

	for (; curr; curr = curr->next) {
		curr_entry = curr->elm;
		if (!(f = create_path_and_file(curr_entry->filename)))
			return false;
		if (!fwrite(curr_data, curr_entry->meta->data_size, 1, f) &&
			curr_entry->meta->data_size > 0)
			return FNC_ERROR_RET(bool, false,
				"Could not fully write to file %s", curr_entry->filename);
		fclose(f);
		curr_data += curr_entry->meta->data_size;
	}
}