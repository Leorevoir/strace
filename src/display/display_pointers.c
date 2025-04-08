/*
** EPITECH PROJECT, 2025
** STRACE
** File description:
** display_pointers
*/

#include "print.h"

char *register_to_string(pid_t pid, size_t reg)
{
    char __attribute__((cleanup(free_char)))*ptr = NULL;
    long int rv = 0;
    size_t size = 0;
    const size_t long_int_size = sizeof(long int);

    ptr = malloc(MAX_BUFFER);
    for (;;) {
        if (size + long_int_size > MAX_BUFFER)
            ptr = realloc(ptr, sizeof(ptr) * 2);
        rv = ptrace(PTRACE_PEEKDATA, pid, reg + size);
        if (rv == -1)
            return NULL;
        memcpy(ptr + size, &rv, long_int_size);
        if (memchr(&rv, 0, long_int_size) != NULL) {
            break;
        }
        size += long_int_size;
    }
    return ptr;
}

static char *get_mode(mode_t mode)
{
    for (size_t i = 0; i < 7; i++) {
        if ((mode & __S_IFMT) == stat_strings[i].mode) {
            return stat_strings[i].string_mode;
        }
    }
    return NULL;
}

char *register_to_stat(pid_t pid, size_t reg)
{
    struct stat statbuf;
    char *result = malloc(MAX_BUFFER);

    if (ptrace(PTRACE_PEEKDATA, pid, reg, &statbuf) == -1) {
        free(result);
        return NULL;
    }
    snprintf(result, MAX_BUFFER, "{st_mode=%s|%o, st_size=%ld, ...}",
        get_mode(statbuf.st_mode), statbuf.st_mode &
        __S_IFMT, statbuf.st_size);
    return result;
}
