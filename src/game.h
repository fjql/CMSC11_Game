#pragma once

enum GameState {
    START,
    PLAY,
    BOSS,
    BATTLE,
    ABOUT,
    WIN,
    LOSE,
    END
};

typedef struct {
    int x, y;
    
    int heal;

    int health, power, defense, recover;
} Player;

typedef struct {
    char* name;
    char* type;

    int health, power, defense;
} Enemy;

typedef struct {
    enum GameState state;

    int map[18][80];
    int map_cur;

    Player player;
    Enemy enemy;
    Enemy boss1;
    Enemy boss2;
} Game;

void game_start(Game*);
void game_battle(Game*, Player*, Enemy*, char);

void game_update(Game*);
void game_draw(Game*);

void game_loop(Game*);

void game_end();