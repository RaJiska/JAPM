cmake_minimum_required (VERSION 2.6)
project (JAPMAAA)

set (JAPM_VERSION_MAJOR 0)
set (JAPM_VERSION_MINOR 1)
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (SRCS
	"${SOURCE_DIR}/main.c"
	"${SOURCE_DIR}/japm.c"
)


configure_file(
	"include/japm_conf.h.in"
	"include/japm_conf.h"
)
include_directories("${INCLUDE_DIR}")

add_executable(JAPM ${SRCS})