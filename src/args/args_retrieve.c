/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: args_retrieve.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Wed Aug 8th 16:23:02 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "args.h"

int args_optind = 1;
int args_opterr = 1;
int args_optopt;
char *args_optarg;

void args_retrieve(int argc, char * const *argv, arguments_t *args)
{
	int opt;

	while ((opt = args_getopt(argc, argv, "hqwv")) != -1) {
		switch (opt) {
		case 'h':
			args_print_help(argv[0], EXIT_SUCCESS);
			break;
		case 'q':
			args->quiet = true;
			break;
		case 'w':
			args->no_warning = true;
			break;
		case 'v':
			args_print_version();
			/* exit */
		default:
			args_print_help(argv[0], EXIT_FAILURE);
			/* exit */
		}
	}
	if (argc - 1 >= args_optind + 1) {
		args->input = argv[args_optind];
		args->output = argv[args_optind + 1];
	}
	else if (argc - 1 == args_optind)
		args->input = argv[args_optind];
}