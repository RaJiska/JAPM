cmake_minimum_required (VERSION 2.6)
project (JAPM)

set (JAPM_AUTHOR "\"Doriann \\\"Ra'Jiska\\\" Corlouër\"")
set (JAPM_AUTHOR_WEBSITE "\"http://rajiska.fr\"")
set (JAPM_LICENSE "\"BSD-3\"")
set (JAPM_LICENSE_WEBSITE "\"https://opensource.org/licenses/BSD-3-Clause\"")
set (JAPM_NAME_SHORT "\"JAPM\"")
set (JAPM_NAME_COMPLETE "\"Just Another PBO Manager\"")
set (JAPM_VERSION_MAJOR 0)
set (JAPM_VERSION_MINOR 2)
set (JAPM_PATH_MAX_LENGTH 260)

set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set (SRCS
	"${SOURCE_DIR}/main.c"
	"${SOURCE_DIR}/japm.c"
	"${SOURCE_DIR}/args/args_getopt.c"
	"${SOURCE_DIR}/args/args_print_help.c"
	"${SOURCE_DIR}/args/args_print_version.c"
	"${SOURCE_DIR}/args/args_retrieve.c"
	"${SOURCE_DIR}/args/args_validate.c"
	"${SOURCE_DIR}/fs/fs_assemble_path.c"
	"${SOURCE_DIR}/fs/fs_get_file_hierarchy.c"
	"${SOURCE_DIR}/fs/fs_path_is_valid.c"
	"${SOURCE_DIR}/fs/fs_path_clean_windows.c"
	"${SOURCE_DIR}/fs/fs_path_clean_linux.c"
	"${SOURCE_DIR}/fs/fs_path_get_last_link.c"
	"${SOURCE_DIR}/pbo/pbo_open.c"
	"${SOURCE_DIR}/pbo/pbo_create.c"
	"${SOURCE_DIR}/pbo/pbo_get_header_block.c"
	"${SOURCE_DIR}/pbo/pbo_get_data_block.c"
	"${SOURCE_DIR}/pbo/pbo_get_checksum_block.c"
	"${SOURCE_DIR}/pbo/pbo_retrieve_entries.c"
	"${SOURCE_DIR}/pbo/pbo_extract.c"
	"${SOURCE_DIR}/pbo/pbo_decompress.c"
	"${SOURCE_DIR}/pbo/pbo_close.c"
)


configure_file(
	"${INCLUDE_DIR}/japm_conf.h.in"
	"${INCLUDE_DIR}/japm_conf.h"
)

include_directories("${INCLUDE_DIR}")
include_directories("${LIB_DIR}/list/include")
include_directories("${LIB_DIR}/utils/include")

file(GLOB LIBLIST_SRC "${LIB_DIR}/list/src/*.c")
add_library(LIBLIST STATIC ${LIBLIST_SRC})
target_include_directories(LIBLIST PUBLIC "${LIB_DIR}/list/include")
file(GLOB LIBUTILS_SRC "${LIB_DIR}/utils/src/*.c")
add_library(LIBUTILS STATIC ${LIBUTILS_SRC})
target_include_directories(LIBUTILS PUBLIC "${LIB_DIR}/utils/include")

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Winit-self -Wwrite-strings \
	-Wcast-align -Wshadow -Wredundant-decls -Wfloat-equal -Wunreachable-code \
	-Wundef -Wlogical-op -Winline -Wdouble-promotion -Wno-pointer-sign \
	-Wno-unused-variable"
)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Ofast")

add_executable(JAPM ${SRCS})
target_link_libraries(JAPM LIBLIST)
target_link_libraries(JAPM LIBUTILS)