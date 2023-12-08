#pragma once

#define MAP_WIDTH   80
#define MAP_HEIGHT  18 

enum GameState {
    START,
    PLAY,
    INVENTORY,
    WIN,
    LOSE,
    END
};

typedef struct {
    int x;
    int y;

    int health;
    int inventory[10];
} Player;

typedef struct {
    enum GameState state;
    int map[MAP_HEIGHT][MAP_WIDTH];
    Player player;
} Game;

void game_start(Game*);

void game_update(Game*, char);
void game_draw(Game*);

void game_loop(Game *game);

void game_end(Game*);