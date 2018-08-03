/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: japm.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 19:06:08 2018
 */

#ifndef JAPM_H_
#define JAPM_H_

#include <stdio.h>
#include <stdlib.h>

#include "japm_conf.h"

typedef struct
{
	char *input;
	char *output;
} arguments_t;

int japm(const arguments_t *args);

#endif /* JAPM_H_ */