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

    #define LONG_SIZE   sizeof(long int)

/*
 * prints
*/
char *register_to_string(pid_t pid, size_t reg);
char *register_to_stat(pid_t pid, size_t reg);
char *register_to_signed(pid_t pid, size_t reg);
char *register_to_unsigned(pid_t pid, size_t reg);

typedef struct string_mode_s {
    mode_t mode;
    char *string_mode;
} string_mode_t;

static const string_mode_t stat_strings[7] = {
    {S_IFCHR, "S_IFCHR"},
    {S_IFBLK, "S_IFBLK"},
    {S_IFDIR, "S_IFDIR"},
    {S_IFIFO, "S_IFIFO"},
    {S_IFLNK, "S_IFLNK"},
    {S_IFREG, "S_IFREG"},
    {S_IFSOCK, "S_IFSOCK"}
};

#endif
