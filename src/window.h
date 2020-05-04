#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <vector>

#include "sprite.h"
#include "SDL.h"

class Window {
public:
    Window();
    Window(std::size_t height, std::size_t width, std::size_t grid_height, std::size_t grid_width, std::string title);
    ~Window();
    Window(Window& source); // Copy Constructor
    Window& operator=(Window& source); // Copy Assignment
    Window(Window&& source); // Move Constructor
    Window& operator=(Window&& source); // Move Assignment
    SDL_Window* get_sdl_window() const;
    void add_child(Sprite* sprite);
    std::size_t get_height() const;
    std::size_t get_width() const;
    std::size_t get_grid_height() const;
    std::size_t get_grid_width() const;
    std::vector<Sprite*> get_children();
    void set_window_title(int fps, int score);
    void remove_child(int index);

private:
    std::size_t height_;
    std::size_t width_;
    std::size_t grid_height_;
    std::size_t grid_width_;
    SDL_Window* sdl_window_;
    std::string title_;
    std::vector<Sprite*> children_;
};

#endif