/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: japm_conf.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 19:08:00 2018
 */

#ifndef JAPM_CONF_H_
#define JAPM_CONF_H_

#define JAPM_NAME JAPM (Just Another PBO Manager)
#define JAPM_VERSION_MAJOR 0
#define JAPM_VERSION_MINOR 2

#define JAPM_PATH_MAX_LENGTH 260
#define JAPM_PATH_FORBIDDEN_CHARS "<>:\"\\/|?*"
#define JAPM_PATH_FORBIDDEN_ENDCHARS " ."

#define JAPM_UNKNOWN_FILE_DIR "__JAPM__"
#define JAPM_UNKNOWN_FILENAME "unknown"
#define JAPM_UNKNOWN_FILEEXT ".txt"

#define JAPM_FILE_BUFFER 1024

extern const int JAPM_PATH_FORBIDDEN_FILENAMES_COUNT;
extern const char *JAPM_PATH_FORBIDDEN_FILENAMES[];

#endif /* JAPM_CONF_H_ */
