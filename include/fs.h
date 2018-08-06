/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 17:17:03 2018
 */

#ifndef FS_H_
#define FS_H_

#include "japm.h"
#include "list.h"

char *fs_assemble_path(const char *path, const char *file, char *buf);
bool fs_get_file_hierarchy(const char *path, list_t **list);
bool fs_path_is_valid(const char *path);
char *fs_path_clean_windows(char *path);
char *fs_path_clean_linux(char *path);

#endif /* FS_H_ */