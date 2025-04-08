/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** strace.h
*/

#ifndef STRACE_H_
    #define STRACE_H_

    #include "../../include/macro.h"
    #include "../../include/utils.h"
    #include <sys/types.h>
    #include <sys/user.h>

    #define     MAX_SYSCALL     (328)
    #define     EXIT_SIGNAL     (231)
    #define     EXECVE_SIGNAL   (59)

typedef struct flag_s {
    bool p;
    pid_t pid;
    bool s;
} flag_t;

/*
 * global strace struct
 */
typedef struct strace_s {
    pid_t pid;
    char **env;
    flag_t flag;
    const char *prog;
    struct user_regs_struct regs;
} strace_t;

/*
 * safer
 */
void safe_waitpid(pid_t pid, int *stat_loc, int options);
void safe_fork(pid_t *pid);

/*
 * main entry point
 */
void strace_init(strace_t *strace, char **env);

/*
 * ptrace and execvp program
 */
void strace_execvp_prog(strace_t *strace);

/*
 * trace program and display syscalls
 */
void strace_start_tracing(strace_t *strace);
void strace_display_trace(strace_t *strace);

#endif /* STRACE_H_ */
