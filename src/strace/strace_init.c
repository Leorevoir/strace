/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_init.c
*/

#include "strace.h"
#include <unistd.h>

static void strace_ctor(strace_t *strace, const char *filename, char **env)
{
    strace->env = env;
    strace->prog = filename;
    safe_fork(&strace->pid);
}

void strace_init(const char *restrict filename, strace_t *strace, char **env)
{
    strace_ctor(strace, filename, env);
    switch (strace->pid) {
        case 0:
            strace_execvp_prog(strace);
            break;
        default:
            strace_start_tracing(strace);
            break;
    }
}
