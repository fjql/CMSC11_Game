#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "game.h"
#include "graphics.h"
#include "maps.h"

void load_map(Game *game, int map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            game->map[y][x] = map[y][x];
            if (game->map[y][x] == 100) {
                game->player.x = x;
                game->player.y = y;
            }
        }
    }
}

void game_start(Game* game) {
    game->state = START;

    game->player = (Player){
        2, 2,
        100,
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    load_map(game, level_1);
}

void game_update(Game* game) {
    char input = getch();

    if (game->state == START) {
        if (input == 52 || input == 27)
            game->state = END;
        
        if (input == 49)
            game->state = PLAY;
    } else if (game->state == PLAY) {
        if (input == 27)
            game->state = START;

        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            game->map[game->player.y][game->player.x] = 0;

            if (input == 'w' && game->map[game->player.y - 1][game->player.x] == 0)
                game->player.y--;
            else if (input == 's' && game->map[game->player.y + 1][game->player.x] == 0)
                game->player.y++;

            if (input == 'a' && game->map[game->player.y][game->player.x - 1] == 0)
                game->player.x--;
            else if (input == 'd' && game->map[game->player.y][game->player.x + 1] == 0)
                game->player.x++;

            game->map[game->player.y][game->player.x] = 100;
        }
    }
}

void game_draw(Game* game) {
    system("clear");

    if (game->state == START) {
        system("clear");
        puts(title_screen);
    } else if (game->state == PLAY) {
        printf("%s\n", separator);
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                char* prnt = " ";

                switch (game->map[y][x]) {
                    case 1:
                        prnt = "\x1b[0;32mA\x1b[0m";
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

                fputs(prnt, stdout);
            }
            puts("");
        }
        puts(separator);
        printf("HEALTH:\t%i\nPOS:\t(%i, %i)\n", game->player.health, game->player.x, game->player.y);
        puts(separator);
    }
}

void game_loop(Game* game) {
    game_draw(game);

    char input;
    while (game->state != END) {
        game_update(game);
        game_draw(game);
    }

    game_end(game);
}

void game_end(Game* game) {
    system("clear");
}