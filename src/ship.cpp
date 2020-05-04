#include <iostream>

#include "ship.h"
#include "enemy.h"
#include "SDL.h"

Ship::Ship() : x_(0), y_(0), height_(0), width_(0), should_draw_(true) {}

void Ship::draw(SDL_Renderer* sdl_renderer) {
    SDL_Rect block;
    block.w = (window_->get_width() / window_->get_grid_width()) * kShipWidthMultiplier;
    block.h = window_->get_height() / window_->get_grid_height();

    width_ = block.w;
    height_ = block.h;

    block.x = x_ * block.w;
    block.y = window_->get_height() - block.h;

    SDL_SetRenderDrawColor(sdl_renderer, 0, 127, 255, 255);
    SDL_RenderFillRect(sdl_renderer, &block);
}

void Ship::will_move(Sprite_Attribute::Direction direction) {
    switch (direction) {
        case Sprite_Attribute::Direction::up:
            break;
        case Sprite_Attribute::Direction::down:
            break;
        case Sprite_Attribute::Direction::left:
            x_ -= 1;
            break;
        case Sprite_Attribute::Direction::right:
            x_ += 1;
            break;                        
    }
}

void Ship::did_move() {
    // Handle wall collision
    if (x_ < 0) {
        x_ = 0;
    } else if ((x_ * width_) + width_ > window_->get_width()) {
        x_ = (window_->get_width() / width_);
    }

    // Handle enemy collision
    for (std::shared_ptr<Sprite> s : sprites_) {
        Enemy* e = dynamic_cast<Enemy*>(s.get());

        if (e) {
            if ((e->get_x() / kShipWidthMultiplier) == x_ && e->get_y() == window_->get_grid_height()) {
                should_draw_ = false;
            }
        }
    }
}

void Ship::subscribe(std::shared_ptr<Sprite> sprite) {
    sprites_.emplace_back(sprite);
}

void Ship::unsubscribe(int index) {
    sprites_.erase(sprites_.begin() + index);
}

void Ship::set_window(std::shared_ptr<Window> window) {
    window_ = window;
}

bool Ship::should_draw() const {
    return should_draw_;
}

int Ship::get_x() const {
    return x_;
}

int Ship::get_y() const {
    return y_;
}