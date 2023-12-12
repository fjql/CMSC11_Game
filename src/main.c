#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

int main(void) {
    srand(time(NULL));

    Game game;

    game_start(&game);

    game_loop(&game);

    game_end();
}