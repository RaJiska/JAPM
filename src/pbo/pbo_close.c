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

void pbo_close(pbo_t *pbo)
{
	if (munmap(pbo->map, pbo->len) == -1)
		fprintf(stderr, "Could not unmap %s: %s\n", pbo->filename, strerror(errno));
	if (fclose(pbo->f) == EOF)
		fprintf(stderr, "Could not close %s: %s\n", pbo->filename, strerror(errno));
	free(pbo->filename);
}