/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_retrieve_entries.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sat Aug 6 0:04:08 2018
 */

#include <string.h>
#include <ctype.h>
#include "japm.h"
#include "pbo.h"
#include "list.h"
#include "utils.h"

static char *get_unknown_filename(char *buf)
{
	static int unknown_file_no = 0;

	snprintf(buf, JAPM_PATH_MAX_LENGTH, "%s\\%s%d%s",
		JAPM_UNKNOWN_FILE_DIR, JAPM_UNKNOWN_FILENAME,
		unknown_file_no, JAPM_UNKNOWN_FILEEXT);
	++unknown_file_no;
	FNC_WARN("Entry with special name renamed -> %s", buf);
	return buf;
}

static bool path_is_valid(const char *path)
{
	char **wt = utils_strsplit(path, "\\", 0);

	if (!wt)
		return FNC_ERROR_RET(bool, false, "Could not allocate memory");
	for (size_t it = 0; wt[it]; ++it) {
		for (int ij = 0; ij < sizeof(JAPM_PATH_FORBIDDEN_FILENAMES); ++ij) {
			if (!strcmp(JAPM_PATH_FORBIDDEN_FILENAMES[ij], wt[it]))
				return false;
		}

		if (strpbrk(wt[it], JAPM_PATH_FORBIDDEN_CHARS) ||
			strpbrk(wt[it] + strlen(wt[it]) - 1, JAPM_PATH_FORBIDDEN_ENDCHARS))
			return false;
	}
	return true;
}

static const char *get_proper_filename(const char *filename, char *buf)
{
	char *s;
	size_t len = strlen(filename);

	strncpy(buf, filename, JAPM_PATH_MAX_LENGTH - 1)[JAPM_PATH_MAX_LENGTH - 1] = 0;
	while (strstr(buf, "\\\\"))
		while (utils_strreplace(buf, "\\\\", "\\"));
	/* Security Checks */
	if (*buf == '\\' || strstr(buf, "..\\") || !path_is_valid(buf))
		return get_unknown_filename(buf);
	for (size_t it = 0; it < len; ++it) {
		if (!isprint(buf[it]))
			return get_unknown_filename(buf);
	}
	/* Ensure PBO doesn't contain files colliding with our unknown files */
	if ((s = strchr(buf, '\\'))) {
		if (strncmp(buf, JAPM_UNKNOWN_FILE_DIR, s - buf))
			return get_unknown_filename(buf);
	}
	return buf;
}

bool pbo_retrieve_entries(pbo_t *pbo)
{
	pbo_entry_t *entry;
	unsigned char buf[JAPM_PATH_MAX_LENGTH];
	byte_t *curr_block = pbo->map_header_block;

	while (*curr_block) {
		if ((entry = malloc(sizeof(pbo_entry_t))) == NULL)
			return FNC_PERROR_RET(bool, false, "Memory allocation failure");
		entry->filename = strdup(get_proper_filename(curr_block, &buf[0]));
		if (!entry->filename) {
			FNC_PERROR("Memory allocation failure");
			free(entry);
			return false;
		}
		entry->meta = (pbo_entry_meta_t *) (strchr(curr_block, 0) + 1);
		if (!list_push(&pbo->entries, entry)) {
			FNC_PERROR("List allocation failure");
			free(entry->filename);
			free(entry);
			return false;
		}
		curr_block = (((byte_t *) entry->meta) + sizeof(pbo_entry_meta_t));
	}
	return true;
}