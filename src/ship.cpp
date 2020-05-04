#include <iostream>

#include "ship.h"
#include "SDL.h"

Ship::Ship() : x_(0), y_(0), height_(0), width_(0), should_draw_(true) {}

void Ship::draw(SDL_Renderer* sdl_renderer) {
    SDL_Rect block;
    block.w = (window_->get_width() / window_->get_grid_width()) * 4;
    block.h = window_->get_height() / window_->get_grid_height();

    width_ = block.w;
    height_ = block.h;

    block.x = x_ * block.w;
    block.y = window_->get_height() - block.h;

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(sdl_renderer, &block);
}

void Ship::did_move(Sprite_Attribute::Direction direction) {
    switch (direction) {
        case Sprite_Attribute::Direction::up:
            // y_ -= 1.0f;
            break;
        case Sprite_Attribute::Direction::down:
            // y_ += 1.0f;
            break;
        case Sprite_Attribute::Direction::left:
            x_ -= 1.0f;
            break;
        case Sprite_Attribute::Direction::right:
            x_ += 1.0f;
            break;                        
    }

    // Handle wall collision
    if (x_ < 0) {
        x_ = 0.0f;
    } else if ((x_ * width_) + width_ > window_->get_width()) {
        x_ = (window_->get_width() / width_) - 1;
    }
}

void Ship::subscribe(Sprite* sprite) {
    sprites_.push_back(sprite);
}

void Ship::set_window(Window* window) {
    window_ = window;
}

bool Ship::should_draw() const {
    return should_draw_;
}