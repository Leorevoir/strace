/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace_display.c
*/

#include "syscall.h"
#include <sys/ptrace.h>
#include <string.h>

static void display_return(strace_t *strace)
{
    if (strace->regs.orig_rax == EXIT_SIGNAL) {
        fprintf(stderr, "?\n");
        return;
    }
    fprintf(stderr, "0x%llx\n", strace->regs.rax);
}

static char *register_to_string(pid_t pid, size_t reg)
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

static void s_flag_switch_types(strace_t *strace, int types, size_t reg)
{
    switch (types) {
        case NUM:
            fprintf(stderr, "%ld", reg);
            break;
        case STRING:
            fprintf(stderr, "\"%s\"",
                register_to_string(strace->pid, reg));
            break;
        case VOID_P:
            fprintf(stderr, "NULL");
            break;
        default:
            break;
    }
}

static void display_s_flag(strace_t *strace)
{
    const size_t registers[] = {
        strace->regs.rdi,
        strace->regs.rsi,
        strace->regs.rdx,
        strace->regs.rcx,
        strace->regs.r8,
        strace->regs.r9
    };
    int *types = get_type_array(strace->regs.orig_rax);

    for (int i = 0; i != table[strace->regs.orig_rax].arg_count; ++i) {
        s_flag_switch_types(strace, types[i], registers[i]);
        if (i < table[strace->regs.orig_rax].arg_count - 1) {
            fprintf(stderr, ", ");
        }
    }
    fprintf(stderr, ") = ");
    free(types);
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
    }
    display_return(strace);
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
