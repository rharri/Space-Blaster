#include <iostream>

#include "settings.h"
#include "window.h"
#include "game.h"

void atexit_handler() {
    std::cout << "Exit handler" << std::endl;
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