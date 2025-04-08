/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** fork_wait.c
*/

#include "strace.h"
#include <unistd.h>
#include <sys/wait.h>

void safe_waitpid(pid_t pid, int *stat_loc, int options)
{
    pid_t cpid = waitpid(pid, stat_loc, options);

    if (cpid < 0) {
        raise_error("safe_waitpid", "waitpid failed");
    }
}

void safe_fork(pid_t *pid)
{
    *pid = fork();
    if (*pid < 0) {
        raise_error("safe_fork", "fork failed");
    }
}
