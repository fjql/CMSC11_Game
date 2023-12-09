#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "graphics.h"
#include "maps.h"

void game_start(Game* game) {
    game->state = START;

    game->player = (Player){
        2, 2,
        100,
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            game->map[y][x] = level_1[y][x];
            if (game->map[y][x] == 100) {
                game->player.x = x;
                game->player.y = y;
            }
        }
    }
}

void game_update(Game* game, char input) {
    if (game->state == START) {
        if (input == 52 || input == 27)
            game->state = END;
        
        if (input == 49)
            game->state = PLAY;
    } else if (game->state == PLAY) {
        if (input == 27)
            game->state = START;
    }
}

void game_draw(Game* game) {
    system("clear");
    system("clear");

    if (game->state == START) {
        printf("%s", title_screen);
    } else if (game->state == PLAY) {
        printf("%s\n", separator);
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                char* prnt = " ";

                switch (game->map[y][x]) {
                    case 1:
                        prnt = "\x1b[1;32mA\x1b[0m";
                        break;
                    case 2:
                        prnt = "\x1b[0;34mW\x1b[0m";
                        break;
                    case 3:
                        prnt = "\x1b[0;33m#\x1b[0m";
                        break;
                    case 99:
                        prnt = "\x1b[1;30;0mO\x1b[0m";
                        break;
                    case 100:
                        prnt = "\x1b[1;37;0m@\x1b[0m";
                        break;
                }

                printf("%s ", prnt);
            }
            printf("\n");
        }
        printf("%s\n", separator);
        printf("HEALTH:\t%i\nPOS:\t(%i, %i)\n", game->player.health, game->player.x, game->player.y);
        printf("%s\n", separator);
    }
}

void game_loop(Game* game) {
    game_draw(game);

    char input;
    while (game->state != END) {
        input = getch();

        _sleep(100);

        game_update(game, input);
        game_draw(game);
    }

    game_end(game);
}

void game_end(Game* game) {
    system("clear");
}