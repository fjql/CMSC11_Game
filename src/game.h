#pragma once

enum GameState {
    START,
    PLAY,
    INVENTORY,
    BATTLE,
    WIN,
    LOSE,
    END
};

typedef struct {
    int x, y;

    int health, power, defense;
} Player;

typedef struct {
    char* name;
    char* type;

    int health, power, defense;
} Enemy;

typedef struct {
    enum GameState state;
    Player player;
    Enemy enemy;
    int map[18][80];
} Game;

void game_start(Game*);

void game_update(Game*);
void game_draw(Game*);

void game_loop(Game*);

void game_end();