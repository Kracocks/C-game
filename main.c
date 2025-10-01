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

	// Préparer le terminal
    printf("\033[?25l"); // Enlever le curseur
    printf("\033[8;%i;%it", HAUTEUR_TERRAIN+3, LARGEUR_TERRAIN);
    set_conio_terminal_mode();

    // Set terrain
    struct terrain terrain = {HAUTEUR_TERRAIN, LARGEUR_TERRAIN};
    struct object player = {12, 12, 10, 10, 1, 'm', PLAYER};
    struct object idiot = {0, 0, 10, 10, 10, 'i', ENEMY};
    struct object* objects[] = {&player, &idiot};
    int size_objects = sizeof(objects) / sizeof(objects[0]);

    // Variables
    int run = 1;
    int nb_frame = 0;
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
            struct object* object = objects[i];
            switch (objects[i]->type) {

                case PLAYER:
                    break;
                case ENEMY:
                  if (nb_frame % object->vitesse == 0) {
                    set_position(&terrain, object, object->pos_x,
                                 object->pos_y + 1);
                  }
                    if (collision(object, &player)) {
                        run = 0;
                    }
                    break;
                case NPC:
                    break;
                case WALL:
                    break;
                case ITEM:
                    break;
            }
            if (object->type == ENEMY) {
                
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
            struct timespec ts = {.tv_sec = (time_t)remaining, .tv_nsec = (remaining - (time_t)remaining) * 1e9};
            nanosleep(&ts, NULL);
        }
        if (nb_frame >= 1000000000) // remise a zero du compteur de frame pour éviter de dépasser la limite
            nb_frame = 0;
        nb_frame++;
    }
    printf("\033[?25h\r\n");
    return 0;
}