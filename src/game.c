#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>

#include "game.h"
#include "maps.h"
#include "strs.h"
#include "graphics.h"

void game_start(Game* game) {
    game->state = START;

    game->player = (Player){
        2, 2,
        0,
        100, 10, 10, 5
    };

    game->enemy = (Enemy){
        "???", "???",
        100000, 100000, 100000
    };

    game->boss1 = (Enemy){
        "???", "THE YOUNG DRAGON",
        125, 20, 129
    };

    game->boss2 = (Enemy){
        "???", "THE MOM",
        200, 25, 30
    };

    map_load(game, level_1, 0);
}

void game_battle(Game* game, Player* player, Enemy* enemy, char input) {
    if (input == 49) {
        int enemy_block_chance = rand() % 100;
        if (enemy_block_chance < 5)
            return;
            
        enemy->health -= floor((float)10 * ((float)player->power / (float)player->defense)) + (rand() % (player->power / 2));

        int player_block_chance = rand() % 100;
        if (player_block_chance < 7)
            return;
        
        player->health -= 10 * ((float)enemy->power / (float)enemy->defense) + (rand() % (enemy->power / 2));
    }

    if (input == 50) {
        if (player->recover == 0)
            return;

        if (player->health >= 85) {
            player->health += 100 - player->health;
        } else {
            player->health += 15;
        }

        player->recover--;
    }

    if (input == 51) {
        game->state = PLAY;
        game->enemy = (Enemy) {
            "???", "???",
            100000, 100000, 100000
        };
    }

    if (enemy->health <= 0) {
        game->state = PLAY;

        int atk_def_inc = rand() % 10;
        if (atk_def_inc <= 5) {
            player->power++;
        } else {
            player->defense++;
        }

        game->enemy = (Enemy) {
            "???", "???",
            100000, 100000, 100000
        };

        player->recover++;
    }

    if (player->health <= 0) {
        game_start(game);
        game->state = LOSE;
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
    } else if (game->state == LOSE) {
        if (input == 49)
            game->state = START;
    } else if (game->state == PLAY) {
        if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            game->map[game->player.y][game->player.x] = 0;

            if (input == 'w' && game->map[game->player.y - 1][game->player.x] == 0)
                game->player.y--;
            else if (input == 's' && game->map[game->player.y + 1][game->player.x] == 0)
                game->player.y++;

            if (input == 'a' && (game->map[game->player.y][game->player.x - 1] == 0 || game->map[game->player.y][game->player.x - 1] == 99))
                game->player.x--;
            else if (input == 'd' && (game->map[game->player.y][game->player.x + 1] == 0 || game->map[game->player.y][game->player.x + 1] == 99))
                game->player.x++;
            
            if (game->map[game->player.y][game->player.x] == 98) {
                int name_chance = rand() % (sizeof(names) / sizeof(names[0]));
                game->boss1.name = names[name_chance];
                name_chance = rand() % (sizeof(names) / sizeof(names[0]));
                game->boss2.name = names[name_chance];

                game->
            }
            
            if (game->map[game->player.y][game->player.x] == 99) {
                if (game->map_cur == 2 && game->boss1.health > 0)
                    return;
                map_change(game);
            }

            game->player.heal++;
            if (game->player.heal >= 5) {
                if (game->player.health >= 95) {
                    game->player.health += 100 - game->player.health;
                } else {
                    game->player.health += 5;
                }
            }

            game->map[game->player.y][game->player.x] = 100;
        }

        int random_battle_chance = rand() % 100;
        if (random_battle_chance < 5) {
            int name_chance = rand() % (sizeof(names) / sizeof(names[0]));

            game->enemy = (Enemy) {
                names[name_chance], "",
                100, 10, 10
            };

            if (game->map_cur == 0) {
                game->enemy.type = "THE SLIME";
                game->enemy.power = 7;
                game->enemy.defense = 10;
            } else if (game->map_cur == 1) {
                game->enemy.type = "THE SPIDER";
                game->enemy.power = 11;
                game->enemy.defense = 8;
            } else if (game->map_cur == 2) {
                game->enemy.type = "THE SPIDER";
                game->enemy.power = 14;
                game->enemy.defense = 10;
            } else {
                game->enemy.type = "???";
                game->enemy.power = 100000;
                game->enemy.defense = 100000;
            }

            system("cls");

            game->player.heal = 0;

            game->state = BATTLE;
        }
    } else if (game->state == BATTLE) {
        game_battle(game, &game->player, &game->enemy, input);
    }
}

void game_draw(Game* game) {
    system("cls");

    if (game->state == START) {
        system("cls");
        puts(title_screen);
    } else if (game->state == LOSE) {
        system("cls");
        puts(lose_screen);
    } else if (game->state == PLAY) {
        puts(separator);
        map_draw(game->map);
        puts(separator);
        printf("HEALTH:\t%i\nPOW:\t%i\nDEF:\t%i\n", game->player.health, game->player.power, game->player.defense);
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
        printf("HEALTH:\t%i\t||\t1. Attack\nPOW:\t%i\t||\t2. Recover (%i)\nDEF:\t%i\t||\t3. Run\n", game->player.health, game->player.power, game->player.recover, game->player.defense);
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
    system("cls");
}