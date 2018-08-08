/*
** EPITECH PROJECT, 2018
** myftp.h
** File description:
** myftp.h
*/
/**
* \file
* \brief Utils header
*/

#ifndef UTIL_H_
# define UTIL_H_

#include <stdbool.h>
#include <stddef.h>

long long int utils_perror(long long int ret, const char *s, ...);
long long int utils_error(long long int ret, const char *s, ...);
char **utils_strsplit(const char *str, const char *delims, int max_delims);
char *utils_strjoin(char * const *wt, const char *separator);
size_t utils_wt_count(char * const *wt);
char **utils_wt_push(char **wt, const char *s);
char **utils_wt_copy(char * const *wt);
char **utils_wt_pop_front(char **wt, char **str);
void utils_wt_destroy(char **wt);
bool utils_strreplace(char *s, const char *from, const char *to);
char *utils_clearstr(char *s);

#endif /* !UTIL_H_ */
