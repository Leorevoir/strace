/*
** EPITECH PROJECT, 2025
** Lib-OOP-GC
** File description:
** Utils.h
*/

#ifndef UTILS_H_
    #define UTILS_H_

#include <stdio.h>
#include <stdbool.h>

void console_log(FILE *stream, const char *format, ...);
void raise_error(const char *where, const char *why);
bool is_number(const char *str);

#endif /* UTILS_H_ */
