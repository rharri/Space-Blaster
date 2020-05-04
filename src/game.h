#ifndef GAME_H
#define GAME_H

#include <memory>

#include "settings.h"
#include "window.h"
#include "SDL.h"

class Game {
public:
    Game(const Settings& settings);
    ~Game();
    void run();
    int get_score() const;

private:
    void handle_input();
    void update();
    void draw();
    bool is_running_;
    std::size_t score_;
    Settings settings_;
    std::shared_ptr<Window> root_;
    SDL_Renderer* sdl_renderer_;
};

#endif