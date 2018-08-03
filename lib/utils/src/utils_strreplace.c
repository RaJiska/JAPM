/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_strreplace.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Jul 4 15:55:51 2018
 */

#include "utils.h"

static char *str_shiftright(char *str)
{
	int str_len = strlen(str);

	if (str_len <= 0)
		return (str);
	for (int it = str_len; it >= 0; --it)
		*(str + it + 1) = *(str + it);
	return str;
}

static char *str_shiftleft(char *str)
{
	int str_len = strlen(str);

	if (str_len <= 0)
		return str;
	for (int it = 0; it < str_len; ++it)
		*(str + it) = *(str + it + 1);
	return str;
}

static void replace_null(char *s, int len_f, const char *from)
{
	s = strstr(s, from);
	while (s)
	{
		for (int it = 0; it < len_f; ++it)
			str_shiftleft(s);
		s = strstr(s, from);
	}
}

static void prepare_space(char *s, int len_f, int len_t)
{
	int it = 0;

	if (len_f == len_t)
		return;
	if (len_f > len_t)
	{
		for (; len_t != (len_f - it); ++it)
			str_shiftleft(s);
	}
	else
	{
		for (; (len_f + it) != len_t; ++it)
			str_shiftright(s);
	}
}

bool utils_strreplace(char *s, const char *from, const char *to)
{
	int len_f;
	int len_t;

	len_f = strlen(from);
	if (!to) {
		replace_null(s, len_f, from);
		return (strstr(s, from) != NULL);
	}
	len_t = strlen(to);
	s = strstr(s, from);
	if (!s)
		return false;
	prepare_space(s, len_f, len_t);
	strncpy(s, to, len_t);
	return (strstr(s, from) != NULL);
}