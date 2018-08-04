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
#include "list.h"

#define PBO_MAGIC { \
	0x00, 0x73, 0x72, 0x65, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define PBO_MAGICALT { \
	0x0A, 0x73, 0x72, 0x65, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }
#define PBO_MAGIC_SZ 21
#define PBO_MAGICALT_SZ 22
#define PBO_PACK_UNCOMPRESSED 0x00000000
#define PBO_PACK_PACKED 0x43707273
#define PBO_PACK_PE 0x56657273

typedef struct
{
	uint32_t packing;
	uint32_t original_size;
	uint32_t garbage;
	uint32_t timestamp;
	uint32_t data_size;
} pbo_entry_meta_t;

typedef struct
{
	unsigned char *filename;
	pbo_entry_meta_t *meta;
} pbo_entry_t;

typedef struct
{
	FILE *f;
	size_t len;
	void *map;
	char *filename;
	list_t *entries;
} pbo_t;

bool pbo_open(const char *file, pbo_t *pbo);
void pbo_retrieve_entries(pbo_t *pbo);
void pbo_close(pbo_t *pbo);

#endif /* PBO_H_ */