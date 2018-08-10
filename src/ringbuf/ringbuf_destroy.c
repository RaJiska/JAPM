/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: ringbuf_destroy.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 21:20:32 2018
 */

#include "ringbuf.h"

void ringbuf_destroy(ringbuf_t *ringbuf)
{
	free(ringbuf->buffer);
}