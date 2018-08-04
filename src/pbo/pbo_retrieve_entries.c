/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_retrieve_entries.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sat Aug 6 0:04:08 2018
 */

#include <string.h>
#include "japm.h"
#include "pbo.h"
#include "list.h"
#include "utils.h"

static inline byte_t *skip_header_and_extension(byte_t *map)
{
	if (*map == 0xA0)
		map += PBO_MAGIC_SZ;
	else {
		map += PBO_MAGICALT_SZ;
		for (; *map || *(map + 1); ++map);
		map += 2;
	}
	return map;
}

void pbo_retrieve_entries(pbo_t *pbo)
{
	pbo_entry_t *entry;
	byte_t *curr_block = skip_header_and_extension(pbo->map);

	while (*curr_block) {
		if ((entry = malloc(sizeof(pbo_entry_t))) == NULL) {
			FNC_PERROR("Memory allocation failure");
			break;
		}
		entry->filename = curr_block;
		entry->meta = (pbo_entry_meta_t *) (strchr(curr_block, 0) + 1);
		if (!list_push(&pbo->entries, entry)) {
			FNC_PERROR("List allocation failure");
			free(entry);
		}
		curr_block =  (((byte_t *) entry->meta) + sizeof(pbo_entry_meta_t));
	}
}