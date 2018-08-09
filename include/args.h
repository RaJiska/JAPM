/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: args.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Wed Aug 8th 16:13:38 2018
 */

#ifndef ARGS_H_
#define ARGS_H_

#include <stdbool.h>

/* Required for our custom getopt */
extern int args_optind;
extern int args_opterr;
extern int args_optopt;
extern char *args_optarg;

typedef struct
{
	char *input;
	char *output;
	bool quiet;
	bool no_warning;
} arguments_t;

extern const arguments_t *ARGS;

int args_getopt(int argc, char * const argv[], const char *optstring);
void args_retrieve(int argc, char * const *argv, arguments_t *args);
void args_print_help(const char *myself, int exit_code);
void args_print_version(void);
bool args_validate(const arguments_t *args);

#endif /* ARGS_H_ */