/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_close.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 23:23:25 2018
 */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/mman.h>
#include "pbo.h"
#include "utils.h"

void pbo_close(pbo_t *pbo)
{
	if (munmap(pbo->map, pbo->len) == -1)
		FNC_WARN("Could not unmap %s\n", pbo->filename);
	if (fclose(pbo->f) == EOF)
		FNC_WARN("Could not close %s\n", pbo->filename);
	free(pbo->filename);
	while (pbo->entries) {
		free(((pbo_entry_t *) (pbo->entries->elm))->filename);
		free(pbo->entries->elm);
		list_pop(&pbo->entries, pbo->entries);
	}
}