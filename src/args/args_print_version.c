/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: args_print_version.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Wed Aug 8th 16:50:17 2018
 */

#include <stdio.h>
#include "japm.h"
#include "args.h"

void args_print_version(void)
{
	printf(JAPM_NAME_SHORT " (" JAPM_NAME_COMPLETE ") version %d.%d compiled on " __DATE__ " " __TIME__ "\n"
		"\n"
		"Copyright (C) " JAPM_AUTHOR " <" JAPM_AUTHOR_WEBSITE ">\n"
		"License " JAPM_LICENSE " <" JAPM_LICENSE_WEBSITE ">\n",
		JAPM_VERSION_MAJOR, JAPM_VERSION_MINOR);
	exit(EXIT_SUCCESS);
}