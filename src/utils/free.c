/*
** EPITECH PROJECT, 2025
** PSU-strace
** File description:
** free.c
*/

#include <stdlib.h>

void free_char(char **ptr)
{
    if (*ptr) {
        free(*ptr);
        *ptr = NULL;
    }
}
