/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: list.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:43:19 2018
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdbool.h>
#include <stddef.h>

enum e_list
{
	LIST_FREE_BEG = -1,
	LIST_FREE_NOT,
	LIST_FREE_PTR,
	LIST_FREE_FNC,
	LIST_FREE_END
};

typedef struct list_s
{
	void *elm;
	struct list_s *next;
	struct list_s *prev;
	struct list_s *end;
} list_t;

bool list_push(list_t **list, void *element);
size_t list_count(const list_t *list);
void list_pop(list_t **list, const list_t *element);
void list_pop_by_elm(list_t **list, const void *element);
void *list_get_by_elm(list_t *list, const void *elm);
void list_print(list_t *list, void (*fnc_print)(void *));
void list_destroy(list_t **node, int free_lvl, void (*fnc)(void *));

#endif /* LIST_H_ */
