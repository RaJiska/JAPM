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
#define STRINGIFY(elm) #elm
#define TOSTRING(elm) STRINGIFY(elm)


#define FNC_WARN(elm, ...) utils_perror(0, __FILE__ ":" TOSTRING(__LINE__) ": WARNING: " elm, ##__VA_ARGS__)
#define FNC_WARN_RET(type, ret, elm, ...) ((type) (FNC_WARN(elm, ##__VA_ARGS__)))
#define FNC_PERROR(elm, ...) utils_perror(0, __FILE__ ":" TOSTRING(__LINE__) ": ERROR: " elm, ##__VA_ARGS__)
#define FNC_PERROR_RET(type, ret, elm, ...) ((type) (FNC_PERROR(elm, ##__VA_ARGS__)))
#define FNC_ERROR(elm, ...) utils_error(0, __FILE__ ":" TOSTRING(__LINE__) ": ERROR: " elm, ##__VA_ARGS__)
#define FNC_ERROR_RET(type, ret, elm, ...) ((type) (FNC_ERROR(elm, ##__VA_ARGS__)))

typedef unsigned char byte_t;

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