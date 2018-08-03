/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list_pop.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#include "list.h"

static void free_element(list_t **node)
{
	list_t *bak;

	if ((*node)->prev != NULL)
		(*node)->prev->next = (*node)->next;
	if ((*node)->next != NULL)
		(*node)->next->prev = (*node)->prev;
	bak = (*node)->next;
	free(*node);
	*node = bak;
}

void list_pop(list_t **list, const list_t *element)
{
	list_t *node = *list;
	list_t *bak;

	while (node)
	{
		if (node != element) {
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