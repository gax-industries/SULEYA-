/*
** EPITECH PROJECT, 2018
** __pretty_much_accurate__runner
** File description:
** hidden stuff. don't look !
*/

#include "headers.h"

void exit_full_custom(void)
{
    __asm__("mov $60, %rax");
    __asm__("mov $84, %rdi");
    __asm__("syscall");
}

void* malloc_safe(size_t size)
{
    void *res;

    res = malloc(size);
    if (res == NULL)
        exit_full_custom();
    return (res);
}

float randf(void)
{
    return ((float)rand() / (float)RAND_MAX);
}
