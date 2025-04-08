/*
** EPITECH PROJECT, 2025
** STRACE
** File description:
** get_type_array
*/

#include <stddef.h>
#include "syscall.h"

int *get_type_array(size_t id)
{
    int *type_array = malloc(sizeof(int) * 6);

    type_array[0] = table[id].type1;
    type_array[1] = table[id].type2;
    type_array[2] = table[id].type3;
    type_array[3] = table[id].type4;
    type_array[4] = table[id].type5;
    type_array[5] = table[id].type6;
    return type_array;
}
