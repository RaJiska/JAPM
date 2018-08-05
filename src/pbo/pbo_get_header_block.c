/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_get_header_start.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sun Aug 0 11:31:33 2018
 */

#include "japm.h"
#include "pbo.h"

byte_t *pbo_get_header_block(byte_t *map)
{
	byte_t *map_original = map;

	map += PBO_MAGIC_SZ;
	if (!*map)
		++map;
	else {
		for (; *map || *(map + 1); ++map);
		map += 2;
	}
	return map;
}