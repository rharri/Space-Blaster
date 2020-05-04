#include <iostream>

#include "enemy.h"
#include "SDL.h"

Enemy::Enemy() : x_(0), y_(0), height_(0), width_(0), should_draw_(true) {}

void Enemy::draw(SDL_Renderer* sdl_renderer) {
    SDL_Rect block;
    block.w = window_->get_width() / window_->get_grid_width();
    block.h = window_->get_height() / window_->get_grid_height();

    width_ = block.w;
    height_ = block.h;

    block.x = x_ * block.w;
    block.y = y_ * block.h;

    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(sdl_renderer, &block);
}

void Enemy::will_move(Sprite_Attribute::Direction direction) {
    y_ += 1;
}

void Enemy::did_move() {
    if ((y_ * height_) + height_ > window_->get_height()) {
        // y_ = 0;
        should_draw_ = false;
    }
}

void Enemy::subscribe(Sprite* sprite) {
    sprites_.push_back(sprite);
}

void Enemy::unsubscribe(int index) {
    sprites_.erase(sprites_.begin() + index);
}

void Enemy::set_window(Window* window) {
    window_ = window;
}

bool Enemy::should_draw() const {
    return should_draw_;
}

int Enemy::get_x() const {
    return x_;
}

int Enemy::get_y() const {
    return y_;
}