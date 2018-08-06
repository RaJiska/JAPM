/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_retrieve_entries.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sat Aug 5th 0:04:08 2018
 */

#include <string.h>
#include <ctype.h>
#include "japm.h"
#include "pbo.h"
#include "fs.h"
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

static const char *get_proper_filename(const char *filename, char *buf)
{
	char *s;

	strncpy(buf, filename, JAPM_PATH_MAX_LENGTH - 1)[JAPM_PATH_MAX_LENGTH - 1] = 0;
	fs_path_clean_windows(buf);
	if (!fs_path_is_valid(buf))
		return get_unknown_filename(buf);
	/* Ensure PBO doesn't contain files colliding with our unknown files */
	if ((s = strchr(buf, '\\'))) {
		if (!strncmp(buf, JAPM_UNKNOWN_FILE_DIR, s - buf))
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