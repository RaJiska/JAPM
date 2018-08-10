/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: ringbuf_write.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 19:28:14 2018
 */

#include <string.h>
#include "japm.h"
#include "ringbuf.h"

/* Requires optimization */
void ringbuf_write(ringbuf_t *ringbuf, const void *buf, size_t sz)
{
	static bool first = true;
	bool alter_read = false;
	size_t remain = (ringbuf->write_ptr + sz > ringbuf->buffer + ringbuf->max_sz)
		? (ringbuf->write_ptr + sz) - (ringbuf->buffer + ringbuf->max_sz)
		: 0;

	/* Amen */
	if ((ringbuf->read_ptr < ringbuf->write_ptr &&
		(remain && remain + ringbuf->buffer > ringbuf->read_ptr)) ||
		(((ringbuf->read_ptr >= ringbuf->write_ptr && !first) ||
		(ringbuf->read_ptr > ringbuf->write_ptr)) &&
		((ringbuf->write_ptr + sz >= ringbuf->read_ptr) || remain)))
		alter_read = true;
	first = false;
	if (remain) {
		memcpy(ringbuf->write_ptr, buf, sz - remain);
		memcpy(ringbuf->buffer, buf + (sz - remain), remain);
		ringbuf->write_ptr = ringbuf->buffer + remain;
		if (alter_read)
			ringbuf->read_ptr = ringbuf->write_ptr;
	}
	else {
		memcpy(ringbuf->write_ptr, buf, sz);
		ringbuf->write_ptr += sz;
		if (alter_read)
			ringbuf->read_ptr = ringbuf->write_ptr;
	}
}