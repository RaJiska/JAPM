/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_create.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 17:08:46 2018
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "pbo.h"
#include "fs.h"
#include "utils.h"

static bool write_files(const char *pbo_name, FILE *f, const list_t *hierarchy)
{
	FILE *file;
	unsigned char buf[JAPM_FILE_BUFFER];
	size_t read_len;

	for (; hierarchy; hierarchy = hierarchy->next) {
		COND_PRINTF(!ARGS->quiet, "Packing %s\n", (char *) hierarchy->elm);
		if (!(file = fopen(hierarchy->elm, "rb"))) {
			fclose(file);
			return FNC_ERROR_RET(bool, false, "Could not read file %s", hierarchy->elm);;
		}
		while ((read_len = fread(&buf[0], 1, JAPM_FILE_BUFFER, file))) {
			if (!fwrite(&buf[0], read_len, 1, f)) {
				fclose(file);
				return FNC_ERROR_RET(bool, false, "Could not write to file %s", pbo_name);
			}
		}
		if (ferror(file)) {
			fclose(file);
			return FNC_ERROR_RET(bool, false, "Could not read from file %s", hierarchy->elm);
		}
		fclose(file);
	}
	return true;
}

static bool write_headers(const char *pbo, const list_t *hierarchy, size_t path_len, FILE *f)
{
	char *str;
	struct stat st;
	pbo_entry_meta_t meta = { 0 };
	unsigned char last_header[1 + sizeof(pbo_entry_meta_t)] = { 0 };

	for (const list_t *curr = hierarchy; curr; curr = curr->next) {
		if (stat(curr->elm, &st) == -1)
			return FNC_PERROR_RET(bool, false, "Could not stat file %s", curr->elm);
		meta.data_size = st.st_size;
		if (!(str = strdup(curr->elm + path_len)))
			return FNC_PERROR_RET(bool, false, "Could not allocate memory");
		while (utils_strreplace(str, "/", "\\"));
		if (!fwrite(str, strlen(str) + 1, 1, f) ||
			!fwrite(&meta, sizeof(pbo_entry_meta_t), 1, f)) {
			return FNC_PERROR_RET(bool, false, "Could not write to file %s", pbo);
		}
		free(str);
	}
	if (!fwrite(&last_header[0], 1 + sizeof(pbo_entry_meta_t), 1, f))
		return FNC_PERROR_RET(bool, false, "Could not write to file %s", pbo);
	return true;
}

/* TODO: Add some cool multi threading (queue system) & list pop*/
bool pbo_create(const char *path, const char *pbo)
{
	FILE *f = fopen(pbo, "wb");
	list_t *hierarchy;
	size_t path_len = strlen(path);

	if (!f)
		return FNC_PERROR_RET(bool, false, "Could not open file %s", pbo);
	if (!fwrite(&PBO_MAGIC[0], PBO_MAGIC_SZ, 1, f) || !fwrite(&(char *) { 0 }, 1, 1, f))
		return FNC_PERROR_RET(bool, false, "Could not write to file %s", pbo);
	COND_PRINTF(!ARGS->quiet, "Retrieving File Hierarchy of %s\n", path);
	if (!fs_get_file_hierarchy(path, &hierarchy))
		return false;
	COND_PRINTF(!ARGS->quiet, "Building File Bank: \n\n");
	for (; *(path + path_len) == '/'; ++path_len); /* Remove leading sepatator */
	if (!write_headers(pbo, hierarchy, path_len, f) || !write_files(pbo, f, hierarchy)) {
		list_destroy(&hierarchy, LIST_FREE_PTR, NULL);
		return false;
	}
	list_destroy(&hierarchy, LIST_FREE_PTR, NULL);
	fclose(f);
	COND_PRINTF(!ARGS->quiet, "\nFiles Bank Built at %s\n", pbo);
	return true;
}