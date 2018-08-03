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

bool pbo_open(const char *file, pbo_t *pbo)
{
	pbo->filename = strdup(file);
	if ((pbo->f = fopen(file, "rb")) == NULL) {
		fprintf(stderr, "Could not open %s: %s\n", file, strerror(errno));
		return false;
	}
	if (fseek(pbo->f, 0, SEEK_END) == -1 || (pbo->len = ftell(pbo->f) == -1)) {
		fprintf(stderr, "Could not get size of %s: %s\n", file, strerror(errno));
		return false;
	}
	if ((pbo->map = mmap(NULL, pbo->len, PROT_READ, MAP_SHARED, fileno(pbo->f), 0)) == (void *) -1) {
		fprintf(stderr, "Could not map %s: %s\n", file, strerror(errno));
		return false;
	}
	return true;
}