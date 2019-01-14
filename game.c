/*
** EPITECH PROJECT, 2018
** __pretty_much_accurate__runner
** File description:
** main
*/

#include "headers.h"

static int poll_events(cn_t *cn)
{
    sfEvent event;

    if (!sfRenderWindow_isOpen(cn->win.window))
        return (0);
    while (sfRenderWindow_pollEvent(cn->win.window, &event))
        switch (event.type) {
            case sfEvtClosed:
            sfRenderWindow_close(cn->win.window);
            return (0);
            default:
            break;
        }
    return (1);
}

void cam_ac(cn_t *cn, vec3 speedprv)
{
    float speed = dist3(cn->player.speed);
    float speedprev = dist3(speedprv);

    if ((speed >= speedprev) && (speed > 0.1f))
        cn->cam.shift.x += cn->win.framelen * 2.0f;
    else
        cn->cam.shift.x -= cn->win.framelen * 5.0f;
    if (cn->cam.shift.x > 6.0f)
        cn->cam.shift.x = 6.0f;
    if (cn->cam.shift.x < 0.0f)
        cn->cam.shift.x = 0.0f;
    cn->cam.pos = cn->player.pos;
    cn->cam.pos.z -= 15.0f + cn->cam.shift.x;
    cn->cam.pos.x += cn->player.size.x / 2.0f;
}

obj_t* gen_ter(cn_t *cn, vec3 lastpos, vec2 lastsize, sprite_t *sprite)
{
    float h = ((float)rand() / (float)RAND_MAX) * 2.0f;

    if ((rand() % 100) > 2)
        add_obj_fun(cn, (vec3){lastpos.x + lastsize.x,
        -h - 1.0f - ((float)rand() / (float)RAND_MAX) * 8.0f, lastpos.z},
        (vec2){((float)rand() / (float)RAND_MAX) * 10.0f,
        ((float)rand() / (float)RAND_MAX) * 3.0f}, sprite);
    return (add_obj_fun(cn, (vec3){lastpos.x + lastsize.x, -h, lastpos.z},
    (vec2){((float)rand() / (float)RAND_MAX) * 5.0f, h}, sprite));
}

void gen_pub(cn_t *cn, sprite_t *bendy, sprite_t *tree, vec3 pos)
{
    size_t count = rand() % 50;
    float h;

    for (size_t i = 0; i < count; i++) {
        add_obj_fun(cn, (vec3){pos.x + ((float)rand() / (float)RAND_MAX) * 10.0f,
        pos.y - ((float)rand() / (float)RAND_MAX) * 1.0f - 2.0f,
        pos.z + 8.0f + ((float)rand() / (float)RAND_MAX) * 50.0f},
        (vec2){1.0f, 1.5f + ((float)rand() / (float)RAND_MAX) * 0.5f}, bendy);
    }
    count = rand() % 50;
    for (size_t i = 0; i < count; i++) {
        h = 7.0f + ((float)rand() / (float)RAND_MAX) * 3.0f;
        add_obj_fun(cn, (vec3){pos.x + ((float)rand() / (float)RAND_MAX) * 10.0f,
        pos.y - ((float)rand() / (float)RAND_MAX) * 1.0f - h,
        pos.z + 20.0f + ((float)rand() / (float)RAND_MAX) * 100.0f},
        (vec2){5.0f, h}, tree);
    }
}

obj_t* gen_sky(cn_t *cn, obj_fun_t *last, sprite_t *sky)
{
    return (add_obj_fun(cn, (vec3){last->pos.x + last->size.x, last->pos.y, last->pos.z},
    last->size, sky));
}

void game(cn_t *cn)
{
    obj_t *obj;
    obj_t *lastsky;
    vec3 speedprev = {0.0f, 0.0f, 0.0f};

    cn->player.sprite = cn->s.sprite[S_BASHO];
    cn->player.pos = (vec3){0.0f, -20.0f, 0.0f};
    cn->player.speed = (vec3){0.0f, 0.0f, 0.0f};
    cn->player.maxsx = 14.0;
    cn->player.size = (vec2){1.0f, 2.0f};
    cn->player.is_grounded = 0;
    obj = add_obj_fun(cn, (vec3){-20.0f, 0.0f, 0.0f}, (vec2){10.0f, 5.0f},
    cn->s.sprite[S_PEBBLES_MOD]);
    lastsky = add_obj_fun(cn, (vec3){-1100.0f, -650.0f, 1000.0f},
    (vec2){2500.0f, 1250.0f}, cn->s.sprite[S_SKY]);
    while (poll_events(cn)) {
        poll_input(cn);
        if (((obj_fun_t*)obj->data)->pos.x - cn->player.pos.x < 100.0f) {
            obj = gen_ter(cn, ((obj_fun_t*)obj->data)->pos,
            ((obj_fun_t*)obj->data)->size, cn->s.sprite[S_PEBBLES_MOD]);
            gen_pub(cn, cn->s.sprite[S_BENDY], cn->s.sprite[S_TREE],
            ((obj_fun_t*)obj->data)->pos);
        }
        if (((obj_fun_t*)lastsky->data)->pos.x - cn->player.pos.x < 1000.0f) {
            lastsky = gen_sky(cn, lastsky->data, cn->s.sprite[S_SKY]);
        }
        physx(cn);
        cam_ac(cn, speedprev);
        speedprev = cn->player.speed;
        update_sprites_frame(cn);
        sfRenderWindow_clear(cn->win.window, sfBlue);
        render(cn);
        render_present(cn);
        update_framerate(cn);
    }
}