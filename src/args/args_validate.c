/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: args_validate.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Thu Aug 9th 10:51:54 2018
 */

#include "args.h"

bool args_validate(const arguments_t *args)
{
	if (!args->input)
		return false;
	return true;
}