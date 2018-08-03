cmake_minimum_required (VERSION 2.6)
project (JAPM)

set (JAPM_VERSION_MAJOR 0)
set (JAPM_VERSION_MINOR 1)
set (INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (LIB_DIR "${PROJECT_SOURCE_DIR}/lib")
set (SRCS
	"${SOURCE_DIR}/main.c"
	"${SOURCE_DIR}/japm.c"
	"${SOURCE_DIR}/pbo/pbo_open.c"
	"${SOURCE_DIR}/pbo/pbo_close.c"
)


configure_file(
	"include/japm_conf.h.in"
	"include/japm_conf.h"
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

add_executable(JAPM ${SRCS})
target_link_libraries(JAPM LIBLIST)
target_link_libraries(JAPM LIBUTILS)