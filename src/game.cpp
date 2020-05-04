#include "game.h"
#include "ship.h"
#include "enemy.h"

Game::Game(const Settings& settings) : 
    settings_(settings), 
    is_running_(true), 
    score_(0), 
    root_(new Window(
        settings_.height_, 
        settings_.width_, 
        settings.grid_height_, 
        settings.grid_width_, 
        "Space Blaster")) {
    
    std::shared_ptr<Ship> s(new Ship);
    s->set_window(root_);
    root_->add_child(s);

    for (auto i = 0; i < 8; i++) {
        std::shared_ptr<Enemy> e(new Enemy);
        e->set_window(root_);
        root_->add_child(e);

        s->subscribe(e);
    }

    sdl_renderer_ = SDL_CreateRenderer(
        root_->get_sdl_window(), -1, SDL_RENDERER_ACCELERATED);

    if (!sdl_renderer_) {
        std::cout << "error: Renderer could not be created." << std::endl;
        std::cout << "error: " << SDL_GetError() << std::endl;
    }
}

Game::~Game() {
    SDL_DestroyRenderer(sdl_renderer_);
}

void Game::run() {
    std::uint32_t title_timestamp = SDL_GetTicks();
    std::uint32_t frame_start;
    std::uint32_t frame_end;
    std::uint32_t frame_duration;
    auto frame_count = 0;

    // Game loop
    while(is_running_) {
        frame_start = SDL_GetTicks();

        handle_input();
        update();
        draw();

        frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;

        if (frame_end - title_timestamp >= 1000) {
            root_->set_window_title(frame_count, score_);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        // If the time for this frame is too small (i.e. frame_duration 
        // is smaller than the target ms_per_frame), delay the loop to
        // achieve the correct frame rate.
        if (frame_duration < settings_.ms_per_frame_) {
            SDL_Delay(settings_.ms_per_frame_ - frame_duration);
        }
    }
}

void Game::handle_input() {
    Sprite_Attribute::Direction direction = Sprite_Attribute::Direction::none;

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            is_running_ = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    direction = Sprite_Attribute::Direction::up;
                    break;
                case SDLK_DOWN:
                    direction = Sprite_Attribute::Direction::down;
                    break;
                case SDLK_LEFT:
                    direction = Sprite_Attribute::Direction::left;
                    break;
                case SDLK_RIGHT:
                    direction = Sprite_Attribute::Direction::right;
                    break;                                        
                default:
                    direction = Sprite_Attribute::Direction::none;
                    break;
            }
        }
    }

    for (std::shared_ptr<Sprite> s : root_->get_children()) {
        s->will_move(direction);
    }
}

void Game::update() {
    std::shared_ptr<Sprite> ship;
    int index = 0;
    for (std::shared_ptr<Sprite> s : root_->get_children()) {
        s->did_move();

        if(dynamic_cast<Ship*>(s.get())) {
            ship = s;
        }

        if (!ship->should_draw()) {
            // Ship has collided with enemy.. end the game!
            is_running_ = false;
            return;
        }

        if (!s->should_draw()) {
            // Remove enemy from window
            root_->remove_child(index);

            // The ship no longer needs updates from this enemy
            ship->unsubscribe(index - 1);

            // 10 points for each enemy that passes
            score_ += 10;

            // Increase game speed when score exceeds 1000
            if (score_ > 1000) {
                settings_.set_ms_per_frame(15);
            }

            // Add a new enemy to the game
            std::shared_ptr<Enemy> e(new Enemy);
            e->set_window(root_);
            root_->add_child(e);

            ship->subscribe(e);
        }
        index++;
    }
}

void Game::draw() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 30, 30, 30, 255);
  SDL_RenderClear(sdl_renderer_);

  // Draw sprites
  for (std::shared_ptr<Sprite> s : root_->get_children()) {
      if (s->should_draw()) {
        s->draw(sdl_renderer_);
      }
  }
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer_);
}

int Game::get_score() const {
    return score_;
}