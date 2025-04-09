/*
** EPITECH PROJECT, 2026
** PSU-strace
** File description:
** tests
*/

#include "./include/unit-tests.h"

Test(parse_arguments, parse_arguments_tests)
{
    cr_assert_eq(parse_arguments(0, NULL, NULL), 84);
}

Test(usage, usage_tests)
{
    cr_assert_eq(usage("salut"), 0);
}

Test(free_char, free_char_test)
{
    char *str = strdup("salut");

    free_char(&str);
    cr_assert_eq(str, NULL);
}

Test(is_number, is_number_test)
{
    const char *str = "123456";

    cr_assert_eq(is_number(str), true);
}

Test(get_type_array, get_type_array_test)
{
    int *type = get_type_array(5);

    cr_assert_eq(type[0], 1);
    cr_assert_eq(type[1], 8);
    cr_assert_eq(type[2], 0);
    cr_assert_eq(type[3], 0);
    cr_assert_eq(type[4], 0);
    cr_assert_eq(type[5], 0);
    free(type);
}

Test(strace_display_trace, strace_display_trace_test)
{
    strace_t strace = {0};

    strace.regs.orig_rax = (unsigned long int)-1;
    strace_display_trace(&strace);
}
