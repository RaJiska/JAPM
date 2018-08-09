/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_open.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 4rth 22:51:50 2018
 */

#include <string.h>
#include <errno.h>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/mman.h>
#endif /* _WIN32 */
#include "pbo.h"
#include "japm.h"
#include "utils.h"

bool pbo_open(const char *file, pbo_t *pbo)
{
	if ((pbo->f = fopen(file, "rb")) == NULL)
		return FNC_PERROR_RET(bool, false, "Could not open %s", file);
	if (fseeko(pbo->f, 0, SEEK_END) == -1 || (pbo->len = ftello(pbo->f)) == -1)
		return FNC_PERROR_RET(bool, false, "Could not get size of %s", file);
#ifdef _WIN32
	if (!(pbo->map_handle = CreateFileMappingA((intptr_t) _get_osfhandle(_fileno(pbo->f)), NULL, PAGE_READONLY, 0, pbo->len, NULL)))
		return false;
	if (!(pbo->map = MapViewOfFileEx(pbo->map_handle, FILE_MAP_READ, 0, 0, 0, NULL)))
		return false;
#else
	if ((pbo->map = mmap(NULL, pbo->len, PROT_READ, MAP_SHARED, fileno(pbo->f), 0)) == (void *) -1)
		return FNC_PERROR_RET(bool, false, "Could not map %s", file);
#endif /* _WIN32 */
	if (memcmp(pbo->map, &PBO_MAGIC[0], PBO_MAGIC_SZ))
		return FNC_ERROR_RET(bool, false, "Incorrect magic bytes in %s", file);
	pbo->filename = strdup(file);
	pbo->entries = NULL;
	pbo->map_header_block = pbo_get_header_block(pbo->map);
	pbo->map_data_block = pbo_get_data_block(pbo->map_header_block);
	pbo->map_checksum_block = pbo_get_checksum_block(pbo->map, pbo->len);
	return true;
}