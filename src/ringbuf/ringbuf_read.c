/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: ringbuf_read.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 19:01:01 2018
 */

#include <string.h>
#include "ringbuf.h"

void ringbuf_read(ringbuf_t *ringbuf, void *buf, size_t sz)
{
	bool alter_read = false;
	size_t remain = (ringbuf->read_ptr + sz > ringbuf->buffer + ringbuf->max_sz)
		? (ringbuf->read_ptr + sz) - (ringbuf->buffer + ringbuf->max_sz)
		: 0;

	memcpy(buf, ringbuf->read_ptr, sz - remain);
	if (remain) {
		memcpy(buf + sz - remain, ringbuf->buffer, remain);
		ringbuf->read_ptr = ringbuf->buffer + remain;
	}
	else
		ringbuf->read_ptr += sz;
}