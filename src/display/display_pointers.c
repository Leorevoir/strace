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
    const size_t long_int_size = LONG_SIZE;

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

static struct stat *get_stat(pid_t pid, size_t reg)
{
    struct stat *statbuf = malloc(sizeof(struct stat));
    long data;
    size_t offset = 0;

    for (offset = 0; offset < sizeof(struct stat); offset += LONG_SIZE) {
        data = ptrace(PTRACE_PEEKDATA, pid, reg + offset, NULL);
        if (data == -1) {
            free(statbuf);
            return NULL;
        }
        if (offset + LONG_SIZE > sizeof(struct stat)) {
            memcpy((char *)statbuf + offset, &data,
                sizeof(struct stat) - offset);
        } else {
            memcpy((char *)statbuf + offset, &data, LONG_SIZE);
        }
    }
    return statbuf;
}

static char *get_mode(mode_t mode)
{
    for (int i = 0; i < 7; ++i) {
        if (stat_strings[i].mode == (mode & S_IFMT)) {
            return stat_strings[i].string_mode;
        }
    }
    return "NULL";
}

char *register_to_stat(pid_t pid, size_t reg)
{
    struct stat *statbuf = get_stat(pid, reg);
    char *result = malloc(sizeof(char) * MAX_BUFFER);

    snprintf(result, MAX_BUFFER,
        "{st_mode=%s|%04o, st_size=%ld, ...}", get_mode(statbuf->st_mode),
        statbuf->st_mode & (mode_t)~__S_IFMT, statbuf->st_size);
    return result;
}

char *register_to_void(__attribute__((unused)) pid_t pid,
    __attribute__((unused)) size_t reg)
{
    return "";
}
