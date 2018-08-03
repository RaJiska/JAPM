/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: main.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 19:42:51 2018
 */

#include <stdio.h>
#include "japm.h"

int main(int argc, char * const *argv)
{
	arguments_t args;

	args.input = argv[1];
	args.output = argv[2];
	return (japm(&args));
}