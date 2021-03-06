/*
** EPITECH PROJECT, 2018
** __pretty_much_accurate__runner
** File description:
** some prototypes
*/

#ifndef _SPRITE_H
#define _SPRITE_H

sprite_t* dup_sprite(sprite_t *src);
sprite_t* create_sprite(const char *path);
void destroy_sprite(sprite_t *sprite);

void load_sprites(cn_t *cn);
void unload_sprites(cn_t *cn);
void update_sprites_frame(cn_t *cn);

spritesheet_t* create_spritesheet(const char *path, size_t sprite_size);
void destroy_spritesheet(spritesheet_t *spritesheet);

#endif
