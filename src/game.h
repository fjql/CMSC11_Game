#pragma once

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
    Player player;
    int map[18][80];
} Game;

void game_start(Game*);

void game_update(Game*);
void game_draw(Game*);

void game_loop(Game*);

void game_end();