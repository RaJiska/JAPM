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
#include "pbo.h"
#include "fs.h"
#include "utils.h"

static bool write_headers(const char *pbo, const list_t *hierarchy, size_t path_len, FILE *f)
{
	struct stat st;
	pbo_entry_meta_t meta = { 0 };
	unsigned char last_header[1 + sizeof(pbo_entry_meta_t)] = { 0 };

	for (const list_t *curr = hierarchy; curr; curr = curr->next) {
		if (stat(curr->elm, &st) == -1)
			return FNC_PERROR_RET(bool, false, "Could not stat file %s", curr->elm);
		meta.data_size = st.st_size;
		/* If Linux */
		while (utils_strreplace(curr->elm, "/", "\\"));
		if (!fwrite(curr->elm + path_len, strlen(curr->elm) + 1 - path_len, 1, f) ||
			!fwrite(&meta, sizeof(pbo_entry_meta_t), 1, f)) {
			return FNC_PERROR_RET(bool, false, "Could not write to file %s", pbo);
		}
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
	if (!fs_get_file_hierarchy(path, &hierarchy))
		return false;
	if (!write_headers(pbo, hierarchy, path_len, f))
		return false;
	fclose(f);
	return true;
}