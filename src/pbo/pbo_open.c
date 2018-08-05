/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_open.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 22:51:50 2018
 */

#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include "pbo.h"
#include "japm.h"
#include "utils.h"

bool pbo_open(const char *file, pbo_t *pbo)
{
	if ((pbo->f = fopen(file, "rb")) == NULL)
		return FNC_PERROR_RET(bool, false, "Could not open %s", file);
	if (fseeko(pbo->f, 0, SEEK_END) == -1 || (pbo->len = ftello(pbo->f)) == -1)
		return FNC_PERROR_RET(bool, false, "Could not get size of %s", file);
	if ((pbo->map = mmap(NULL, pbo->len, PROT_READ, MAP_SHARED, fileno(pbo->f), 0)) == (void *) -1)
		return FNC_PERROR_RET(bool, false, "Could not map %s", file);
	if (memcmp(pbo->map, &PBO_MAGIC[0], PBO_MAGIC_SZ))
		return FNC_ERROR_RET(bool, false, "Incorrect magic bytes in %s", file);
	pbo->filename = strdup(file);
	pbo->entries = NULL;
	pbo->map_header_block = pbo_get_header_block(pbo->map);
	pbo->map_data_block = pbo_get_data_block(pbo->map_header_block);
	pbo->map_checksum_block = pbo_get_checksum_block(pbo->map, pbo->len);
	return true;
}