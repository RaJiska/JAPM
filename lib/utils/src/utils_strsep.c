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
	char *found = NULL;

        if (!str)
                return NULL;
        for (size_t it = 0; delims[it]; ++it) {
                if ((found = strchr(*str, delims[it])))
                        break;
        }
        if (found) {
                *found = 0;
                return found + 1;
        }
        return *str;
}