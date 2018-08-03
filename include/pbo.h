/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 22:33:17 2018
 */

#ifndef PBO_H_
#define PBO_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define PBO_MAGIC 0x007372655600000000000000000000000000000000

typedef struct
{
	uint32_t packing;
	uint32_t original_size;
	uint32_t garbage;
	uint32_t timestamp;

} pbo_entry_meta_t;

typedef struct
{
	unsigned char *filename;
	pbo_entry_meta_t *meta;
} pbo_entry_t;

typedef struct
{
	char *filename;
	FILE *f;
	size_t len;
	void *map;
} pbo_t;

bool pbo_open(const char *file, pbo_t *pbo);
void pbo_close(pbo_t *pbo);

#endif /* PBO_H_ */