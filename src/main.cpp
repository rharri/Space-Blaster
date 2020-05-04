#include <iostream>

#include "settings.h"
#include "window.h"
#include "game.h"

// Use std::atexit to call SDL_Quit to clean up resources.
// https://en.cppreference.com/w/cpp/utility/program/atexit
void atexit_handler() {
    SDL_Quit();
}

int main() {
    Settings settings{R"(game.settings)"};

    Game game{settings};
    game.run();

    std::cout << "Final Score: " << game.get_score() << std::endl;
    std::cout << "Thanks for playing!" << std::endl;

    std::atexit(atexit_handler);
}