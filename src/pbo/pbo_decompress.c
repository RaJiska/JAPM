/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: pbo_uncompress.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Sat Aug 11th 9:48:26 2018
 */

#include <string.h>
#include "pbo.h"
#include "utils.h"

static inline bool print_from_ptr(
	FILE *f,
	byte_t *buffer,
	size_t *bytes_buffered,
	uint16_t ptr)
{
	uint16_t real_ptr = (ptr >> 8) | (((ptr >> 4) & 0xF) << 8);
	int to_read = (ptr & 0xF) + 3;
	byte_t data_buf[18];
	ssize_t start_offset = *bytes_buffered - real_ptr;

	if (start_offset < 0)
		return FNC_WARN_RET(bool, false, "Pointer offset < 0 (%lld), skipping file", start_offset);
	for (ssize_t it = 0; it < to_read; ++it) {
		fwrite(buffer + start_offset + it, 1, 1, f);
		buffer[(*bytes_buffered)++] = buffer[start_offset + it];
	}
	return true;
}

void pbo_decompress(FILE *f, const pbo_entry_t *entry, const byte_t *data_start)
{
	byte_t buffer[4096 * PBO_DECOMPRESS_FACTOR];
	size_t bytes_read = 0;
	size_t bytes_buffered = 0;
	byte_t format_byte = data_start[bytes_read++];
	int bit_no = 0;

	while (bytes_read < entry->meta->data_size - 4) {
		if (bit_no >= 8) {
			format_byte = data_start[bytes_read++];
			bit_no = 0;
		}
		if (format_byte & 0x1) { /* Bit is 1: Print raw data */
			fwrite(data_start + bytes_read, 1, 1, f);
			buffer[bytes_buffered++] = data_start[bytes_read++];
		}
		else { /* Bit is 0: Interpret as Ptr */
			if (!print_from_ptr(f, &buffer[0], &bytes_buffered,
			(data_start[bytes_read] << 8) | data_start[bytes_read + 1]))
			break; /* Unhandled case *yet* */
			bytes_read += 2;
		}
		format_byte >>= 1;
		++bit_no;
		if (bytes_buffered > (4096 * (PBO_DECOMPRESS_FACTOR - 1))) {
			memmove(&buffer[0], &buffer[bytes_buffered - 4096], 4096);
			bytes_buffered = 4096;
		}
	}
}