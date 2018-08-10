/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: rinbbuf_create.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 18:41:02 2018
 */

#include "ringbuf.h"
#include "utils.h"

bool ringbuf_init(ringbuf_t *ringbuf, size_t max_size)
{
	if (!(ringbuf->buffer = malloc(max_size)))
		return FNC_PERROR_RET(bool, false, "Could not allocate memory");
	ringbuf->write_ptr = ringbuf->buffer;
	ringbuf->read_ptr = ringbuf->buffer;
	ringbuf->read_sz = 0;
	ringbuf->max_sz = max_size;
	return true;
}