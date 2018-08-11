/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_close.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 4rth 23:23:25 2018
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <sys/mman.h>
#endif /* _WIN32 */
#include "pbo.h"
#include "utils.h"

void pbo_close(pbo_t *pbo)
{
#ifdef _WIN32
	UnmapViewOfFile(pbo->map);
	CloseHandle(pbo->map_handle);
#else
	if (munmap(pbo->map, pbo->len) == -1 && !ARGS->no_warning)
		FNC_WARN("Could not unmap %s\n", pbo->filename);
#endif /* _WIN32 */
	if (fclose(pbo->f) == EOF && !ARGS->no_warning)
		FNC_WARN("Could not close %s\n", pbo->filename);
	free(pbo->filename);
	while (pbo->entries) {
		free(((pbo_entry_t *) (pbo->entries->elm))->filename);
		free(pbo->entries->elm);
		list_pop(&pbo->entries, pbo->entries);
	}
}