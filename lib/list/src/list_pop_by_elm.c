/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list_pop_by_elm.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include "list.h"

static void free_element(list_t **node)
{
	list_t *bak;

	if ((*node)->prev)
		(*node)->prev->next = (*node)->next;
	if ((*node)->next)
		(*node)->next->prev = (*node)->prev;
	bak = (*node)->next;
	free(*node);
	*node = bak;
}

void list_pop_by_elm(list_t **list, const void *element)
{
	list_t *node = *list;
	list_t *bak;

	while (node)
	{
		if (node->elm != element)
		{
			node = node->next;
			continue;
		}
		bak = node;
		if (node == *list && (*list)->next)
			(*list)->next->end = (*list)->end;
		else if ((*list)->end == node)
			(*list)->end = node->prev;
		free_element(&node);
		if (bak == *list)
			*list = node;
		break;
	}
}
