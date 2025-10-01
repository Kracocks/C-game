#define _POSIX_C_SOURCE 199309L

#include "input.h"
#include "object.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#define FPS 60
#define HAUTEUR_TERRAIN 40
#define LARGEUR_TERRAIN 80

int main(void) {
	// Set frame
	double frame_time = 1.0 / FPS;

	// Set user action
    printf("\e[?25l"); // Enlever le curseur
    printf("\033[8;%i;%it", HAUTEUR_TERRAIN+3, LARGEUR_TERRAIN);
    set_conio_terminal_mode();

    // Set terrain
    struct terrain terrain = {HAUTEUR_TERRAIN, LARGEUR_TERRAIN};
    struct object player = {12, 12, 10, 10, 'm', PLAYER};
    struct object idiot = {0, 0, 10, 10, 'i', ENEMY};
    struct object* objects[] = {&player, &idiot};
    int size_objects = sizeof(objects) / sizeof(objects[0]);

    int run = 1;
    char user_input;

    while (run) {
        struct timespec ts_debut;
        clock_gettime(CLOCK_MONOTONIC, &ts_debut);

        // Affichage
        afficher_terrain(&terrain, objects, size_objects);
        printf("\r\n"); // Messages
        printf("avancer : z ; reculer : s ; doite : q ; gauche : d\r\n"); // Informations
        printf("quitter : n");

        // NPC actions
        for (int i = 0; i < size_objects; ++i) {
            if (objects[i]->type == ENEMY) {
<<<<<<< HEAD
            // printf("ennemy bougé");
=======
                set_position(&terrain, objects[i], objects[i]->pos_x, objects[i]->pos_y+1);
                if (collision(objects[i], &player)) {
                    run = 0;
                }
>>>>>>> d4097d16079369a5ea0192a186a19842a6c95644
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
        clock_gettime(CLOCK_MONOTONIC, &ts_fin);
        double temps_s = ts_fin.tv_sec - ts_debut.tv_sec;
        double temps_ns = ts_fin.tv_nsec - ts_debut.tv_nsec;
        double elapsed = temps_s + temps_ns / 1e9;

        double remaining = frame_time - elapsed;
        if (remaining > 0) {
            struct timespec ts = {.tv_sec = (time_t)remaining,
                                    .tv_nsec = (remaining - (time_t)remaining) * 1e9};
            nanosleep(&ts, NULL);
        }
    }
    printf("\e[?25h\r\n");
    return 0;
}