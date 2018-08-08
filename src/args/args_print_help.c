/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: args_print_help.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Wed Aug 8th 16:31:49 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "args.h"

void args_print_help(const char *myself, int exit_code)
{
	printf("USAGE\n"
		"\t%s [OPTIONS] input [output]\n"
		"\n"
		"OPTIONS\n"
		"\t-h\tPrint this help message and discard other options\n"
		"\t-q\tQuiet: does not print status\n"
		"\t-w\tNo warning\n"
		"\t-v\tDisplay version and discard other options\n", myself);
	exit(exit_code);
}