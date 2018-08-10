/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: rinbuf.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 18:41:21 2018
 */

#ifndef RINGBUF_H_
#define RINGBUF_H_

#include <stddef.h>
#include <stdbool.h>
#include "japm.h"

typedef struct
{
	byte_t *buffer;
	byte_t *write_ptr;
	byte_t *read_ptr;
	size_t read_sz;
	size_t max_sz;
} ringbuf_t;

bool ringbuf_init(ringbuf_t *ringbuf, size_t max_size);
void ringbuf_write(ringbuf_t *ringbuf, const void *buf, size_t sz);
void ringbuf_read(ringbuf_t *ringbuf, void *buf, size_t sz);
void ringbuf_destroy(ringbuf_t *ringbuf);

#endif /* RINGBUF_H_ */