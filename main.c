#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include "object.h"
#include "input.h"
#include <fcntl.h>
#include <stdint.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define AVANCER 'z'
#define RECULER 's'
#define GAUCHE 'q'
#define DROITE 'd'
#define FPS 10

int main(void) {
	// Set frame
	double frame_time = 1.0 / FPS;

	// Set user action
	set_conio_terminal_mode();

    // Set terrain
    struct terrain terrain = {30, 80};
    struct object player = {12, 12, 10, 10, 'm', PLAYER};
    struct object idiot = {0, 0, 10, 10, 'i', ENEMY};
    struct object* objects[] = {&player, &idiot};
    int size_objects = sizeof(objects) / sizeof(objects[0]);

    int run = 1;
    char user_input;

    while (run) {
        struct timespec ts_debut;
        clock_gettime(CLOCK_REALTIME, &ts_debut);

        // Affichage
        afficher_terrain(&terrain, objects, size_objects);

        // NPC actions
        for (int i = 0; i < size_objects; ++i) {
            if (objects[i]->type == ENEMY) {
            // printf("ennemy bougé\n");
            }
        }

        // User actions
        if (kbhit()) {
            user_input = (getchar());
            switch (user_input) {
            case 'n':
                run = 0;
                break;
            case 'z':
                set_position(&terrain, &player, player.pos_x, player.pos_y - 1);
                break;
            case 'q':
                set_position(&terrain, &player, player.pos_x - 1, player.pos_y);
                break;
            case 's':
                set_position(&terrain, &player, player.pos_x, player.pos_y + 1);
                break;
            case 'd':
                set_position(&terrain, &player, player.pos_x + 1, player.pos_y);
                break;
            }
        }

        struct timespec ts_fin;
        clock_gettime(CLOCK_REALTIME, &ts_fin);
        double temps_s = ts_fin.tv_sec - ts_debut.tv_sec;
        double remaining_time = frame_time - temps_s;
        sleep(remaining_time);
    }
}