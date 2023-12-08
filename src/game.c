#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "graphics.h"

void game_start(Game* game) {
    game->state = START;

    game->player = (Player){
        2, 2,
        100,
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            game->map[y][x] = 0;
        }
    }
}

void game_draw(Game* game) {
    //system("clear");

    if (game->state == START) {
        printf("%s", title);
    } else if (game->state == PLAY) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                char* prnt = ".";

                switch (game->map[y][x]) {
                    case 1:
                        prnt = "#";
                        break;
                }

                printf("%s", prnt);
            }
            printf("\n");
        }
    }
}

void game_loop(Game* game) {
    game_draw(game);

    char input;
    while (input = getch()) {
        if (input == 27)
            break;

        game_draw(game);
    }
}