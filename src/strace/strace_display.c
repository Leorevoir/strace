/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_display.c
*/

#include "syscall.h"

static void display_return(strace_t *strace)
{
    if (strace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "?\n");
        return;
    }
    fprintf(stderr, "0x%llx\n", strace->regs.rax);
}

static void display_s_flag(__attribute_maybe_unused__ strace_t *strace)
{
    const size_t registers[] = {
        strace->regs.rdi,
        strace->regs.rsi,
        strace->regs.rdx,
        strace->regs.rcx,
        strace->regs.r8,
        strace->regs.r9
    };

    for (int i = 0; i < table[strace->regs.orig_rax].arg_count; ++i) {
        if (table[i].)
    }
}

static void display_args(strace_t *strace)
{
    const size_t registers[] = {
        strace->regs.rdi,
        strace->regs.rsi,
        strace->regs.rdx,
        strace->regs.rcx,
        strace->regs.r8,
        strace->regs.r9
    };

    for (int i = 0; i != table[strace->regs.orig_rax].arg_count; ++i) {
        fprintf(stderr, "0x%lx", registers[i]);
        if (i != table[strace->regs.orig_rax].arg_count - 1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ") = ");
}

static void display_syscalls(strace_t *strace)
{
    fprintf(stderr, "%s(", table[strace->regs.orig_rax].name);
    if (strace->regs.orig_rax == EXECVE_SIGNAL) {
        fprintf(stderr, "\"%s\", [\"%s\"], ", strace->prog, strace->prog);
        return;
    }
    if (strace->flag.s) {
        display_s_flag(strace);
    } else {
        display_args(strace);
        display_return(strace);
    }
}

void strace_display_trace(strace_t *strace)
{
    if ((ssize_t)strace->regs.orig_rax == -1) {
        return;
    }
    if (strace->regs.orig_rax > MAX_SYSCALL) {
        fprintf(stderr, "Unknown\n");
        return;
    }
    display_syscalls(strace);
    if (strace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "+++ exited with %lld +++\n", strace->regs.rdi);
    }
}
