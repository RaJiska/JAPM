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
#include <stdbool.h>
#include "japm_conf.h"

#define UNUSED __attribute__((unused))
#define FNC_PERROR(elm) utils_perror(elm, __FILE__, __LINE__, 0)
#define FNC_PERROR_RET(elm, type, ret) ((type) (utils_perror(elm, __FILE__, __LINE__, ret)))
#define FNC_ERROR(elm) utils_error(elm, __FILE__, __LINE__, 0)
#define FNC_ERROR_RET(elm, type, ret) ((type) (utils_error(elm, __FILE__, __LINE__, ret)))

typedef struct
{
	char *input;
	char *output;
} arguments_t;

enum japm_action
{
	JAPM_ACTION_NONE,
	JAPM_ACTION_PACK,
	JAPM_ACTION_UNPACK
};

bool japm(const arguments_t *args);

#endif /* JAPM_H_ */