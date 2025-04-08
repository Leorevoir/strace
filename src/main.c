/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** main.c
*/

#include "strace.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int usage(const char *prgrm)
{
    console_log(stderr, "USAGE: %s [-s] [-p <pid>] <command>", prgrm);
    return SUCCESS;
}

int parse_arguments(int argc, char **argv, char **env)
{
    strace_t strace = {0};

    if (argc < 2) {
        console_log(stderr, "%s\n%s", STRACE_NO_ARG, STRACE_TRY);
        return ERROR;
    }
    if (argc == 2 &&
        (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0)) {
        return usage(argv[0]);
    }
    if (argc == 3 && strcmp(argv[1], "-p") == 0 && is_number(argv[2])) {
        strace.flag.pid = atoi(argv[2]);
        strace.flag.p = true;
    }
    if (argc == 3 && strcmp(argv[1], "-s") == 0) {
        strace.flag.s = true;
        strace.prog = argv[2];
    }
    strace_init(&strace, env);
    return SUCCESS;
}

int main(int argc, char **argv, char **env)
{
    return parse_arguments(argc, argv, env);
}
