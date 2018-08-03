/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list_count.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:45:58 2018
 */

#include <stdlib.h>
#include "list.h"

size_t list_count(const list_t *list)
{
	size_t it = 0;

	for (; list; list = list->next, ++it);
	return it;
}