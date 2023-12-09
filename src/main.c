#include <stdio.h>
#include <stdlib.h>

#include "game.h"

int main(void) {
    Game game;

    game_start(&game);

    game_loop(&game);

    game_end();
}