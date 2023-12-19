#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

int main(void) {
    srand(time(NULL));

    Game game;

    // Initialize game stuff.
    game_start(&game);

    // The game loop - where all the drawing and updates happen.
    game_loop(&game);

    // Stuff that happens when game ends.
    game_end();
}