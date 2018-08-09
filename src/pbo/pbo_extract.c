/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_extract.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sun Aug 5th 11:22:14 2018
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

/* TODO: Pass it to the FS block */
static FILE *create_path_and_file(const char *base_dir, const char *path)
{
	FILE *f;
	char buffer[JAPM_PATH_MAX_LENGTH] = { 0 };
	char **wt;
	int elem = 0;

	if (strlen(base_dir) + strlen(path) >= JAPM_PATH_MAX_LENGTH)
		return FNC_PERROR_RET(FILE *, NULL, "Path exceeds %d bytes", JAPM_PATH_MAX_LENGTH);
	if (!(wt = utils_strsplit(path, "\\", 0)))
		return FNC_ERROR_RET(FILE *, NULL, "Could not allocate memory");
	strcat(strcpy(&buffer[0], base_dir), "/");
	if (!create_directory(&buffer[0]))
		return NULL;
	for (; wt[elem + 1]; ++elem) {
		strcat(strcpy(&buffer[0], base_dir), "/");
		for (int it = 0; it <= elem; ++it)
			strcat(strcat(&buffer[0], wt[it]), "/");
		if (!create_directory(&buffer[0]))
			return NULL;
	}
	strcat(&buffer[0], wt[elem]);
	if ((f = fopen(&buffer[0], "w+b")) == NULL)
		return FNC_PERROR_RET(FILE *, 0, "Could not create file: %s", &buffer[0]);
	utils_wt_destroy(wt);
	return f;
}

/* TODO:
	- Handle compression
	- Set file last modified
	- Multithreading
*/
bool pbo_extract(const pbo_t *pbo, const char *output_dir)
{
	FILE *f = NULL;
	list_t *curr = pbo->entries;
	pbo_entry_t *curr_entry;
	byte_t *curr_data = pbo->map_data_block;

	for (; curr; curr = curr->next) {
		curr_entry = curr->elm;
		if (curr_entry->meta->packing != PBO_PACK_UNCOMPRESSED) {
			FNC_WARN("File %s compressed - " JAPM_NAME_SHORT " does not"
				"support this feature yet: Skipping", curr_entry->filename);
			continue;
		}
		COND_PRINTF(!ARGS->quiet, "Extracting %s\n", curr_entry->filename);
		if (!(f = create_path_and_file(output_dir, curr_entry->filename)))
			return false;
		if (!fwrite(curr_data, curr_entry->meta->data_size, 1, f) &&
			curr_entry->meta->data_size > 0)
			return FNC_ERROR_RET(bool, false,
				"Could not write to file %s", curr_entry->filename);
		fclose(f);
		curr_data += curr_entry->meta->data_size;
	}
	COND_PRINTF(!ARGS->quiet, "\nFiles Bank Extracted in %s\n", output_dir);
	return true;
}