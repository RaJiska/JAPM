/*
 * Copyright	: Copyright (C) 2018 Doriann Corlouër. All rights reserved.
 * File		: japm_conf.h
 * Author	: Doriann "Ra'Jiska" Corlouër
 * Created	: Fri Aug 5 19:08:00 2018
 */

#ifndef JAPM_CONF_H_
#define JAPM_CONF_H_

#define JAPM_AUTHOR "Doriann \"Ra'Jiska\" Corlouër"
#define JAPM_AUTHOR_WEBSITE "http://rajiska.fr"
#define JAPM_LICENSE "BSD-3"
#define JAPM_LICENSE_WEBSITE "https://opensource.org/licenses/BSD-3-Clause"
#define JAPM_NAME_SHORT "JAPM"
#define JAPM_NAME_COMPLETE "Just Another PBO Manager"
#define JAPM_VERSION_MAJOR 0
#define JAPM_VERSION_MINOR 2

#define JAPM_PATH_MAX_LENGTH 260
#define JAPM_PATH_FORBIDDEN_CHARS "<>:\"\\/|?*"
#define JAPM_PATH_FORBIDDEN_ENDCHARS " ."

#ifdef _WIN32
	#define JAPM_PATH_SEP '\\'
	#define JAPM_PATH_SEP_STR "\\"
#else
	#define JAPM_PATH_SEP '/'
	#define JAPM_PATH_SEP_STR "/"
#endif /* _WIN32 */

#define JAPM_UNKNOWN_FILE_DIR "__JAPM__"
#define JAPM_UNKNOWN_FILENAME "unknown"
#define JAPM_UNKNOWN_FILEEXT ".txt"

#define JAPM_FILE_BUFFER 1024

extern const int JAPM_PATH_FORBIDDEN_FILENAMES_COUNT;
extern const char *JAPM_PATH_FORBIDDEN_FILENAMES[];

#endif /* JAPM_CONF_H_ */
