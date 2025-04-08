/*
** EPITECH PROJECT, 2025
** STRACE
** File description:
** print
*/

#ifndef INCLUDED_PRINT_H
    #define INCLUDED_PRINT_H

    #include "strace.h"
    #include <stdlib.h>
    #include <string.h>
    #include <sys/ptrace.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <stddef.h>
/*
 * prints
*/
char *register_to_string(pid_t pid, size_t reg);
char *register_to_stat(pid_t pid, size_t reg);

typedef struct string_mode_s {
    mode_t mode;
    char *string_mode;
} string_mode_t;

static const string_mode_t stat_strings[7] = {
    {__S_IFCHR, "S_IFCHR"},
    {__S_IFBLK, "S_IFBLK"},
    {__S_IFDIR, "S_IFDIR"},
    {__S_IFIFO, "S_IFIFO"},
    {__S_IFLNK, "S_IFLNK"},
    {__S_IFREG, "S_IFREG"},
    {__S_IFSOCK, "S_IFSOCK"}
};

#endif
