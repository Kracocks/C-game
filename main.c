#include "object.h"
#include <stdio.h>

#define AVANCER 'z'
#define RECULER 's'
#define GAUCHE 'q'
#define DROITE 'd'

int main(void) {
    struct terrain terrain = {100, 100};
    struct object player = {12, 30, 20, 10, 'm', PLAYER};
    struct object idiot = {0, 0, 20, 10, 'i', ENEMY};
    struct object* objects[] = {&player, &idiot};
    int size_objects = sizeof(objects) / sizeof(objects[0]);

    int run = 1;
    char user_input;
    while (run) {
        afficher_terrain(&terrain, objects, size_objects);

        // User actions
        scanf("%c", &user_input);
        switch (user_input) {
            case 'n':
                run = 0;
                break;
            case 'z':
                set_position(&terrain, &player, player.pos_x, player.pos_y + 1);
                break;
            case 'q':
                set_position(&terrain, &player, player.pos_x, player.pos_y + 1);
                break;
            case 's':
                set_position(&terrain, &player, player.pos_x, player.pos_y + 1);
                break;
            case 'd':
                set_position(&terrain, &player, player.pos_x, player.pos_y + 1);
                break;
        }

        // NPC actions
        for (int i = 0; i < size_objects; ++i) {
            if (objects[i]->type == ENEMY) {

            }
        }
    }
}