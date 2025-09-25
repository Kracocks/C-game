#ifndef OBJECT_H
#define OBJECT_H

enum Type {
    PLAYER,
    ENEMY,
    NPC,
    WALL,
    ITEM
};

struct object {
    int pos_x;
    int pos_y;
    int hauteur;
    int largeur;
    char repr;
    enum Type type;
};

struct terrain {
    int hauteur;
    int largeur;
};

int collision(struct object* o1, struct object* o2);
void set_position(struct terrain* terrain, struct object *o, int new_x, int new_y);
void afficher_terrain(struct terrain* terrain, struct object* o_presents[], int nb_obj);

#endif