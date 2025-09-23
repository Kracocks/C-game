#include <stdio.h>
#include "object.h"

int collision(struct object* o1, struct object* o2) {
    return 
        o1->pos_x < o2->pos_x + o2->largeur &&
        o1->pos_x + o1->largeur > o2->pos_x &&
        o1->pos_y < o2->pos_y + o2->hauteur &&
        o1->pos_y + o1->hauteur > o2->pos_y;
}

void set_position(struct terrain* terrain, struct object* o, int new_x, int new_y) {
    if (new_x >= 0 && new_y >= 0 && new_x + o->largeur <= terrain->largeur && new_y + o->hauteur <= terrain->hauteur) {
        o->pos_x = new_x;
        o->pos_y = new_y;
    }
}

void afficher_terrain(struct terrain* terrain, struct object* o_presents[], int nb_obj) {
    for (int y = 0; y < terrain->hauteur; ++y) {
        for (int x = 0; x < terrain->largeur; ++x) {
            int printed = 0;
            for (int i_o = 0; i_o < nb_obj; ++i_o) {
                if (x >= o_presents[i_o]->pos_x && x < o_presents[i_o]->pos_x + o_presents[i_o]->largeur &&
                    y >= o_presents[i_o]->pos_y && y < o_presents[i_o]->pos_y + o_presents[i_o]->hauteur) {
                    printf("%c", o_presents[i_o]->repr);
                    printed = 1;
                    break;
                }
            }
            if (!printed) {
                printf(".");
            }
        }
        printf("\n");
    }
}