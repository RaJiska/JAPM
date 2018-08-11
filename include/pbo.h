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
#ifdef _WIN32
	#include <windows.h>
#endif /* _WIN32 */
#include "japm.h"
#include "list.h"

static const unsigned char PBO_MAGIC[] = {
	0x00, 0x73, 0x72, 0x65, 0x56, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define PBO_MAGIC_SZ sizeof(PBO_MAGIC)
#define PBO_CHECKSUM_SZ 20
#define PBO_PACK_UNCOMPRESSED 0x00000000
#define PBO_PACK_PACKED 0x43707273
#define PBO_PACK_PE 0x56657273

#define PBO_DECOMPRESS_FACTOR 3

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
	off_t len;
#ifdef _WIN32
	HANDLE map_handle;
#endif /* _WIN32 */
	byte_t *map;
	byte_t *map_header_block;
	byte_t *map_data_block;
	byte_t *map_checksum_block;
	char *filename;
	list_t *entries;
} pbo_t;

bool pbo_open(const char *file, pbo_t *pbo);
bool pbo_create(const char *path, const char *pbo);
byte_t *pbo_get_header_block(byte_t *map);
byte_t *pbo_get_data_block(byte_t *header_block);
byte_t *pbo_get_checksum_block(byte_t *map, size_t file_len);
bool pbo_retrieve_entries(pbo_t *pbo);
bool pbo_extract(const pbo_t *pbo, const char *output_dir);
void pbo_decompress(FILE *f, const pbo_entry_t *entry, const byte_t *data_start);
void pbo_close(pbo_t *pbo);

#endif /* PBO_H_ */