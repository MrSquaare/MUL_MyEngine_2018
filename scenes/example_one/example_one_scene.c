/*
** EPITECH PROJECT, 2018
** example_one_scene.c
** File description:
** No description
*/

#include <SFML/Graphics.h>
#include "engine/components.h"
#include "engine/managers.h"
#include "scenes.h"

void example_one_scene_events(scene_t *self, global_t *global)
{
    data_t *data = (data_t *) self->data;
    buttons_manager(data->btn_list, self, global);
    modal_list_events(data->mdl_list, global, 0);
    if (global->evt.type == sfEvtKeyPressed) {
        if (global->evt.key.code == sfKeyNumpad0)
            self->nid = EXAMPLE_TWO;
        if (global->evt.key.code == sfKeyM)
            modal_list_run(data->mdl_list, sfTrue, 0);
    }
}

void example_one_scene_render(scene_t *self, global_t *global)
{
    data_t *data = (data_t *) self->data;

    if (data) {
        button_list_display(data->btn_list, global, 0);
        dyn_sprite_list_display(data->dspt_list, global, 0);
        sprite_list_display(data->spt_list, global, 0);
        modal_list_render(data->mdl_list, global, 0);
    }
}

void example_one_scene_update(scene_t *self, global_t *global)
{
    data_t *data = (data_t *) self->data;

    if (data) {
        rclock_list_update(data->rclk_list, 0);
        while (rclock_list_time(data->rclk_list, 1, 1)) {
            animation_list_animate(data->anim_list, 0);
            button_list_animate(data->btn_list, 0);
            dyn_sprite_list_animate(data->dspt_list, 0);
        }
        while (rclock_list_time(data->rclk_list, 0.05, 2)) {
            animation_list_move(data->anim_list, sfTrue, 0);
            dyn_sprite_list_move(data->dspt_list, sfFalse, 0);
        }
        rclock_list_restart(data->rclk_list, 3);
        modal_list_update(data->mdl_list, global, 0);
    }
}

void example_one_scene_delete(scene_t *self)
{
    if (self->data)
        data_delete(self->data);
}

scene_t *example_one_scene_init(global_t *global)
{
    scene_t *scene = scene_create(EXAMPLE_ONE);

    scene->data = example_one_data_create(scene, global);
    scene->dlt = example_one_scene_delete;
    scene->evt = example_one_scene_events;
    scene->rdr = example_one_scene_render;
    scene->upd = example_one_scene_update;
    return (scene);
}