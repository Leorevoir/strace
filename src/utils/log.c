/*
** EPITECH PROJECT, 2025
** Lib
** File description:
** log.c
*/

#include "../../include/macro.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

/*
* more aesthetics & useful than just a printf
*/
void console_log(FILE *stream, const char *restrict format, ...)
{
    va_list args;

    va_start(args, format);
    vfprintf(stream, format, args);
    fprintf(stream, "\n");
    va_end(args);
    fflush(stream);
}

/*
* as the name says
*/
void raise_error(const char *restrict where, const char *restrict why)
{
    console_log(stderr, "ERROR:\t%s\n\t%s\n", where, why);
    exit(ERROR);
}
