/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list_get_by_elm.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:45:54 2018
 */

#include <stdlib.h>
#include "list.h"

void *list_get_by_elm(list_t *list, const void *elm)
{
	for (; list; list = list->next)
	{
		if (list->elm == elm)
			return list;
	}
	return NULL;
}