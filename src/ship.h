#ifndef SHIP_H
#define SHIP_H

#include <vector>

#include "sprite.h"
#include "window.h"

class Ship : public Sprite {
public:
    Ship();
    void draw(SDL_Renderer* sdl_renderer) override;
    void will_move(Sprite_Attribute::Direction direction) override;
    void did_move() override;
    void subscribe(Sprite* sprite) override;
    void unsubscribe(int index) override;
    void set_window(Window* window) override;
    bool should_draw() const override;
    int get_x() const override;
    int get_y() const override;

private:
    int x_;
    int y_;
    int height_;
    int width_;
    bool should_draw_;
    Window* window_;
    std::vector<Sprite*> sprites_;
};

#endif