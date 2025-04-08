/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_start.c
*/

#include "strace.h"
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <unistd.h>

void strace_execvp_prog(strace_t *strace)
{
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1) {
        raise_error("strace_execvp_prog", "ptrace failed");
    }
    if (execvp(strace->prog, (char **)&strace->prog) == -1) {
        raise_error("strace_execvp_prog", "execvp failed");
    }
}

void strace_start_tracing(strace_t *strace)
{
    int stat_loc = 0;

    safe_waitpid(strace->pid, &stat_loc, 0);
    if (ptrace(
        PTRACE_SETOPTIONS, strace->pid, NULL, PTRACE_O_TRACEEXIT) == -1) {
        perror("ptrace");
    }
    while (!WIFEXITED(stat_loc)) {
        if (ptrace(PTRACE_GETREGS, strace->pid, NULL, &strace->regs) == -1) {
            perror("ptrace");
        }
        strace_display_trace(strace);
        if (ptrace(PTRACE_SINGLESTEP, strace->pid, NULL, 0) == -1) {
            perror("ptrace");
        }
        safe_waitpid(strace->pid, &stat_loc, 0);
    }
}
