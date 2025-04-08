/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_init.c
*/

#include "strace.h"
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

static void strace_ctor(strace_t *strace, char *filename, char **env)
{
    strace->env = env;
    strace->prog = filename;
    safe_fork(&strace->pid);
}

static char *get_filename(const char *restrict path, const strace_t *strace)
{
    char process_path[PATH_MAX] = {0};

    if (strace->flag.p) {
        snprintf(process_path, sizeof(process_path),
            PROC_PATH, strace->flag.pid);
        if (!is_executable(process_path)) {
            raise_error("get_filename", "no such PID");
        }
        return strdup(process_path);
    }
    return strdup(path);
}

void strace_init(const char *restrict filename, strace_t *strace, char **env)
{
    strace_ctor(strace, get_filename(filename, strace), env);
    switch (strace->pid) {
        case 0:
            strace_execvp_prog(strace);
            break;
        default:
            strace_start_tracing(strace);
            break;
    }
    free(strace->prog);
}
