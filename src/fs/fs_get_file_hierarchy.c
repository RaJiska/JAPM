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
#ifdef _WIN32
	#include <windows.h>
#endif /* _WIN32 */
#include "fs.h"
#include "japm.h"
#include "utils.h"

#ifdef _WIN32
static bool recursive_retrieve(const char *path, list_t **list)
{
	char *full_path = malloc(strlen(path) + 4 + 1);
	WIN32_FIND_DATA file;
	HANDLE find;

	if (!full_path)
		return FNC_PERROR_RET(bool, false, "Could not allocate memory");
	snprintf(full_path, PATH_MAX + 4, "%s\\*.*", path);
	if (!(find = FindFirstFile(full_path, &file)))
		return false;
	free(full_path);
	do
	{
		if (!strcmp(".", file.cFileName) || !strcmp("..", file.cFileName))
			continue;
		if (!(full_path = malloc(strlen(path) + 1 + strlen(file.cFileName) + 1))) {
			FNC_PERROR("Could not allocate memory");
			FindClose(find);
			return false;
		}
		sprintf(full_path, "%s\\%s", path, file.cFileName);
		if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && !recursive_retrieve(full_path, list)) {
			free(full_path);
			FindClose(find);
			return false;
		}
		if (!list_push(list, full_path)) {
			FNC_PERROR("Could not allocate memory");
			free(full_path);
			FindClose(find);
			return false;
		}
	} while (FindNextFile(find, &file));
	FindClose(find);
	return true;
}
#else
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

		if (!strcmp(".", &file->d_name[0]) || !strcmp("..", &file->d_name[0]))
			continue;
		if (!(full_path = fs_assemble_path(path, &file->d_name[0], NULL))) {
			closedir(dir);
			return false;
		}
		if (file->d_type == DT_DIR) {
			if (!recursive_retrieve(full_path, list)) {
				free(full_path);
				closedir(dir);
				return false;
			}
			continue;
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
#endif /* _WIN32 */

/* Note: Only retrieves files */
bool fs_get_file_hierarchy(const char *path, list_t **list)
{
	char *path_cleaned = strdup(path);

	if (!path)
		return FNC_PERROR_RET(bool, false, "Could not allocated memory");
#ifdef _WIN32
	fs_path_clean_windows(path_cleaned);
#else
	fs_path_clean_linux(path_cleaned);
#endif /* _WIN32 */
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