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
#include <stddef.h>

static int count_env_var(char **env)
{
    int res = 0;

    for (; env[res]; ++res);
    return 1;
}

static void strace_ctor(strace_t *strace, char *filename, char **env)
{
    strace->env = env;
    strace->prog = filename;
    strace->env_count = count_env_var(env);
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

void strace_init(strace_t *strace, char **env)
{
    strace_ctor(strace, get_filename(strace->prog, strace), env);
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
