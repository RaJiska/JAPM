/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: utils_strsep.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 9:31:51 2018
 */

#include <string.h>
#include "utils.h"

char *utils_strsep(char **str, const char *delims)
{
        char *start = *str;
	char *found;

        if (!*str)
                return NULL;
        if ((found = strpbrk(start, delims))) {
                *found = 0;
                *str = found + 1;
        }
        else
                *str = NULL;
        return start;
}