#ifndef SPRITE_H
#define SPRITE_H

#include <cstdint>

#include "SDL.h"

class Window;

namespace Sprite_Attribute {
    enum class Direction {up, down, left, right, none};
};

class Sprite {
public:
    virtual void draw(SDL_Renderer* sdl_renderer) = 0;
    virtual void will_move(Sprite_Attribute::Direction direction) = 0;
    virtual void did_move() = 0;
    virtual void subscribe(Sprite* sprite) = 0;
    virtual void unsubscribe(int index) = 0;
    virtual void set_window(Window* window) = 0;
    virtual bool should_draw() const = 0;
    virtual int get_x() const = 0;
    virtual int get_y() const = 0;
};

#endif