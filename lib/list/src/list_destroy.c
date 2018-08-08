/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list_destroy.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include <stdlib.h>
#include "list.h"

void list_destroy(list_t **node, int free_lvl, void (*fnc)(void *))
{
	list_t *list;
	list_t *bak;

	if (free_lvl <= LIST_FREE_BEG || free_lvl >= LIST_FREE_END)
		return;
	list = *node;
	while (list)
	{
		if (free_lvl == LIST_FREE_PTR)
		{
			free(list->elm);
			list->elm = NULL;
		}
		else if (free_lvl == LIST_FREE_FNC && fnc != NULL)
			(*fnc)(list->elm);
		bak = list->next;
		free(list);
		list = bak;
	}
	*node = NULL;
}
