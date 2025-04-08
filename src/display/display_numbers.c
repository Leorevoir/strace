/*
** EPITECH PROJECT, 2025
** STRACE
** File description:
** display_numbers
*/

#include "print.h"

char *register_to_signed(__attribute_maybe_unused__ pid_t pid, size_t reg)
{
    char *result = malloc(32);

    snprintf(result, 32, "%ld", reg);
    return result;
}

char *register_to_unsigned(__attribute_maybe_unused__ pid_t pid, size_t reg)
{
    char *result = malloc(32);

    snprintf(result, 32, "%lu", reg);
    return result;
}
