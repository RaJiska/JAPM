/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: fs.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Mon Aug 6th 17:17:03 2018
 */

#ifndef FS_H_
#define FS_H_

#include "japm.h"

bool fs_path_is_valid(const char *path);
void fs_path_clean(char *path);

#endif /* FS_H_ */