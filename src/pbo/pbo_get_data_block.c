/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_get_data_block.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sun Aug 5th 11:32:59 2018
 */

#include <string.h>
#include "pbo.h"

byte_t *pbo_get_data_block(byte_t *header_block)
{
	for (; *header_block;
		header_block = strchr(header_block, 0) + 1 + sizeof(pbo_entry_meta_t));
	/* Skipping the last null entry */
	return (header_block + 1 + sizeof(pbo_entry_meta_t));
}