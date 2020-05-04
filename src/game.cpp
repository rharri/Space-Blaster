#include "game.h"
#include "ship.h"

Game::Game(const Settings& settings) : 
    settings_(settings), is_running_(true), score_(0) {
    
    root_ = new Window{
        settings_.height_, 
        settings_.width_, 
        settings.grid_height_, 
        settings.grid_width_, 
        "Space Blaster"};

    Ship* s = new Ship;
    s->set_window(root_);
    root_->add_child(s);

    sdl_renderer_ = SDL_CreateRenderer(
        root_->get_sdl_window(), -1, SDL_RENDERER_ACCELERATED);

    if (!sdl_renderer_) {
        std::cout << "error: Renderer could not be created." << std::endl;
        std::cout << "error: " << SDL_GetError() << std::endl;
    }
}

Game::~Game() {
    SDL_Quit();
}

void Game::run() {
    std::uint32_t title_timestamp = SDL_GetTicks();
    std::uint32_t frame_start;
    std::uint32_t frame_end;
    std::uint32_t frame_duration;
    auto frame_count = 0;

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
    Sprite_Attribute::Direction direction;

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

    for (Sprite* s : root_->get_children()) {
      s->did_move(direction);
    }
}

void Game::update() {

}

void Game::draw() {
  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 30, 30, 30, 255);
  SDL_RenderClear(sdl_renderer_);

  // Draw sprites
  for (Sprite* s : root_->get_children()) {
      if (s->should_draw()) {
        s->draw(sdl_renderer_);
      }
  }
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer_);
}