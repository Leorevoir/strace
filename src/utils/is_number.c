/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** main.c
*/

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

bool is_number(const char *str)
{
    for (size_t i = 0; str[i]; ++i) {
        if (isdigit(str[i])) {
            continue;
        }
        return false;
    }
    return true;
}
