/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: main.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 19:42:51 2018
 */

#include <stdio.h>
#include "japm.h"

static void print_help(const char *myself, int exit_code)
{
	printf("USAGE\n"
		"\t%s [OPTIONS] input output\n"
		"\n"
		"OPTIONS\n"
		"\t-q\tQuiet: does not print status\n"
		"\t-w\tNo warning\n", myself);
	exit(exit_code);
}

int main(int argc, char * const *argv)
{
	arguments_t args;

	if (argc < 3)
		print_help(argv[0], EXIT_FAILURE);
	args.input = argv[1];
	args.output = argv[2];
	return ((japm(&args)) ? EXIT_SUCCESS : EXIT_FAILURE);
}