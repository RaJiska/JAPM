/*
	Originally written by Christopher "skeeto" Wellons
	Free of use under the "unlicensed" license
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "args.h"

int args_getopt(int argc, char * const argv[], const char *optstring)
{
	static int optpos = 1;
	const char *arg;
	(void)argc;

	/* Reset? */
	if (args_optind == 0) {
		args_optind = 1;
		optpos = 1;
	}

	arg = argv[args_optind];
	if (arg && strcmp(arg, "--") == 0) {
		args_optind++;
		return -1;
	} else if (!arg || arg[0] != '-' || !isalnum(arg[1])) {
		return -1;
	} else {
		const char *opt = strchr(optstring, arg[optpos]);
		args_optopt = arg[optpos];
		if (!opt) {
			if (args_opterr && *optstring != ':')
				fprintf(stderr, "%s: illegal option: %c\n", argv[0], args_optopt);
			return '?';
		} else if (opt[1] == ':') {
			if (arg[optpos + 1]) {
				args_optarg = (char *)arg + optpos + 1;
				args_optind++;
				optpos = 1;
				return args_optopt;
			} else if (argv[args_optind + 1]) {
				args_optarg = (char *)argv[args_optind + 1];
				args_optind += 2;
				optpos = 1;
				return args_optopt;
			} else {
				if (args_opterr && *optstring != ':')
					fprintf(stderr,
						"%s: option requires an argument: %c\n",
						argv[0], args_optopt);
				return *optstring == ':' ? ':' : '?';
			}
		} else {
			if (!arg[++optpos]) {
				args_optind++;
				optpos = 1;
			}
			return args_optopt;
		}
	}
}