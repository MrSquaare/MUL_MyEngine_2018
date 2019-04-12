/*
** EPITECH PROJECT, 2018
** dyn_sprite.c
** File description:
** No description
*/

#include <SFML/Graphics.h>
#include <stdlib.h>
#include "engine/components/dyn_sprite.h"
#include "engine/components/sprite.h"

dyn_sprite_t *dyn_sprite_create(const char *path, sfIntRect rect)
{
    dyn_sprite_t *dyn_sprite = malloc(sizeof(dyn_sprite_t));
    sfVector2f pos = {0, 0};
    sfVector2f vect = {0, 0};

    if (dyn_sprite) {
        dyn_sprite->spt = sprite_create(path);
        dyn_sprite->rect = rect;
        dyn_sprite->road = NULL;
        dyn_sprite->step = 0;
        dyn_sprite->steps = 0;
        dyn_sprite->spd = 5;
        dyn_sprite->agl = 0;
        dyn_sprite->vect = vect;
        dyn_sprite_calculate(dyn_sprite, 0, 0);
        sfSprite_setTextureRect(dyn_sprite->spt->obj, dyn_sprite->rect);
        sprite_set_pos(dyn_sprite->spt, pos);
    }
    return (dyn_sprite);
}

void dyn_sprite_set_rect(dyn_sprite_t *dyn_sprite, sfIntRect rect)
{
    if (dyn_sprite) {
        sprite_set_rect(dyn_sprite->spt, rect);
        dyn_sprite->rect.left = dyn_sprite->spt->rect.left;
        dyn_sprite->rect.top = dyn_sprite->spt->rect.top;
        sfSprite_setTextureRect(dyn_sprite->spt->obj, dyn_sprite->rect);
    }
}

void dyn_sprite_set_road(dyn_sprite_t *dyn_sprite,
        sfVector2f *road, int steps)
{
    sfVector2f *road_m = malloc(sizeof(sfVector2f) * (steps + 1));

    if (dyn_sprite) {
        for (int i = 0; i < steps; ++i)
            road_m[i] = road[i];
        road_m[steps] = road[steps - 1];
        dyn_sprite->road = road_m;
        dyn_sprite->step = 0;
        dyn_sprite->steps = steps;
        dyn_sprite_calculate(dyn_sprite, 0, 1);
        sprite_set_pos(dyn_sprite->spt, dyn_sprite->road[0]);
    }
}

void dyn_sprite_delete(dyn_sprite_t *dyn_sprite)
{
    if (dyn_sprite) {
        sprite_delete(dyn_sprite->spt);
        if (dyn_sprite->road)
            free(dyn_sprite->road);
        free(dyn_sprite);
    }
}