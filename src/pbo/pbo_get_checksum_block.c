/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_get_checksum_block.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sun Aug 5th 11:55:51 2018
 */

#include "pbo.h"

byte_t *pbo_get_checksum_block(byte_t *map, size_t file_len)
{
	return (map + file_len) - PBO_CHECKSUM_SZ;
}