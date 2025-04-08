/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_display.c
*/

#include "syscall.h"

static void display_syscalls(strace_t *strace)
{
    fprintf(stderr, "%s(", table[strace->regs.orig_rax].name);
}

void strace_display_trace(strace_t *strace)
{
    if ((ssize_t)strace->regs.orig_rax == -1) {
        return;
    }
    if (strace->regs.orig_rax > 328) {
        (void)fprintf(stderr, "Unknown\n");
        return;
    }
    display_syscalls(strace);
    if (strace->regs.orig_rax == 231) {
        (void)fprintf(stderr,"+++ exited with %lld +++\n", strace->regs.rdi);
    }
}
