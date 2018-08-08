/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs_get_file_hierarchy.c
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 18:43:30 2018
 */

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include "fs.h"
#include "japm.h"
#include "utils.h"

/* TODO: Multithread the crawling */
static bool recursive_retrieve(const char *path, list_t **list)
{
	DIR *dir = opendir(path);
	struct dirent *file;
	char *full_path;

	if (!dir)
		return FNC_PERROR_RET(bool, false, "Could not open directory %s", path);
	errno = 0;
	while ((file = readdir(dir)) && !errno) {
		/* FOR LINUX */
		if (!strcmp(".", &file->d_name[0]) || !strcmp("..", &file->d_name[0]))
			continue;
		if (!(full_path = fs_assemble_path(path, &file->d_name[0], NULL))) {
			closedir(dir);
			return false;
		}
		if (file->d_type == DT_DIR && !recursive_retrieve(full_path, list)) {
			free(full_path);
			closedir(dir);
			return false;
		}
		if (!list_push(list, full_path)) {
			FNC_PERROR("Could not allocate memory");
			free(full_path);
			closedir(dir);
			return false;
		}
	}
	if (errno)
		return FNC_PERROR_RET(bool, false, "Could not read file in directory %s", path);
	closedir(dir);
	return true;
}

bool fs_get_file_hierarchy(const char *path, list_t **list)
{
	char *path_cleaned = strdup(path);

	if (!path)
		return FNC_PERROR_RET(bool, false, "Could not allocated memory");
	/* TODO: Call clean Windows on WIN32 */
	fs_path_clean_linux(path_cleaned);
	*list = NULL;
	if (!recursive_retrieve(path_cleaned, list)) {
		list_destroy(list, LIST_FREE_PTR, NULL);
		*list = NULL;
		free(path_cleaned);
		return false;
	}
	free(path_cleaned);
	return true;
}