/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: main.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 4rth 19:42:51 2018
 */

#include <stdio.h>
#include "japm.h"

int main(int argc, char * const *argv)
{
	arguments_t args = { 0 };

	if (argc == 0)
		return EXIT_FAILURE;
	args_retrieve(argc, argv, &args);
	return ((japm(&args)) ? EXIT_SUCCESS : EXIT_FAILURE);
}