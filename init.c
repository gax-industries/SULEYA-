/*
** EPITECH PROJECT, 2018
** __pretty_much_accurate__runner
** File description:
** win
*/

#include "headers.h"

cn_t* init(void)
{
    cn_t *res;

    res = malloc_safe(sizeof(cn_t));
    if (!init_win(res))
        return (NULL);
    return (res);
}
