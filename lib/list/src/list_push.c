/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list_push.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:48:04 2018
 */

#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

bool list_push(list_t **list, void *element)
{
	list_t *node = malloc(sizeof(list_t));

	if (!node)
		return false;
	node->elm = element;
	node->next = NULL;
	if (!*list) {
		node->prev = NULL;
		*list = node;
	}
	else {
		node->prev = (*list)->end;
		node->prev->next = node;
	}
	(*list)->end = node;
	return true;
}
