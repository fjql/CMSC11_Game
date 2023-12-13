#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "game.h"
#include "maps.h"
#include "strs.h"
#include "graphics.h"

void game_start(Game* game) {
    game->state = START;

    game->player = (Player){
        2, 2,
        100, 10, 10
    };

    game->enemy = (Enemy) {
        "???", "???",
        100000, 100000, 100000
    };

    game->map_cur = 0;

    for (int y = 0; y < 18; y++) {
        for (int x = 0; x < 80; x++) {
            game->map[y][x] = level_1[y][x];
            if (game->map[y][x] == 100) {
                game->player.x = x;
                game->player.y = y;
            }
        }
    }
}

void game_update(Game* game) {
    char input = getch();

    if (input == 27)
        game->state = END;

    if (game->state == START) {
        if (input == 52)
            game->state = END;
        
        if (input == 49)
            game->state = PLAY;
    } else if (game->state == PLAY) {
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

        int random_battle_chance = rand() % 100;
        if (random_battle_chance < 5) {
            int name_chance = rand() % (sizeof(names) / sizeof(names[0])) % 4;

            game->enemy = (Enemy) {
                names[name_chance], "THE SLIME",
                100, 7, 10
            };

            system("clear");

            game->state = BATTLE;
        }
    } else if (game->state == BATTLE) {
        if (input == 51) {
            game->state = PLAY;
            game->enemy = (Enemy) {
                "???", "???",
                100000, 100000, 100000
            };
        }
    }
}

void game_draw(Game* game) {
    system("clear");

    if (game->state == START) {
        system("clear");
        puts(title_screen);
    } else if (game->state == PLAY) {
        puts(separator);
        map_draw(game->map);
        puts(separator);
        printf("HEALTH:\t%i\nPOW:\t%i\nDEF:\t%i\nPOS:\t(%i, %i)\n", game->player.health, game->player.power, game->player.defense, game->player.x, game->player.y);
        puts(separator);
    } else if (game->state == BATTLE) {
        puts(separator);
        if (game->map_cur == 0) {
            printf(slime, game->enemy.name, game->enemy.type, game->enemy.health);
        } else if (game->map_cur == 1) {
            printf(spider, game->enemy.name, game->enemy.type, game->enemy.health);
        } else {
            printf(slime, game->enemy.name, game->enemy.type, game->enemy.health);
        }
        puts(separator);
        printf("HEALTH:\t%i\t||\t1. Attack\nPOW:\t%i\t||\t2. Drink Health Potion\nDEF:\t%i\t||\t3. Run\n", game->player.health, game->player.power, game->player.defense);
        puts(separator);
    }
}

void game_loop(Game* game) {
    game_draw(game);
    while (game->state != END) {
        game_update(game);
        game_draw(game);
    }
}

void game_end() {
    system("clear");
}