#include <iostream>

#include "window.h"

Window::Window() : height_(0), width_(0), grid_height_(0), grid_width_(0), title_("") {}

Window::Window(std::size_t height, std::size_t width, std::size_t grid_height, std::size_t grid_width, std::string title) : 
    height_(height), width_(width), grid_height_(grid_height), grid_width_(grid_width), title_(title) {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "error: SDL could not initialize." << std::endl;
    std::cout << "error: " << SDL_GetError() << std::endl;
  }

  sdl_window_ = SDL_CreateWindow(
      title_.c_str(), 
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, 
      width_, 
      height_, 
      SDL_WINDOW_SHOWN);

  if (!sdl_window_) {
    std::cout << "error: Window could not be created." << std::endl;
    std::cout << "error: " << SDL_GetError() << std::endl;
  }
}

Window::~Window() {
    SDL_DestroyWindow(sdl_window_);
}

Window::Window(Window& source) {
    height_ = source.height_;
    width_ = source.width_;
    grid_height_ = source.grid_height_;
    grid_width_ = source.grid_width_;
    sdl_window_ = source.sdl_window_;
    title_ = source.title_;
    children_ = source.children_;

    source.height_ = 0;
    source.width_ = 0;
    source.grid_height_ = 0;
    source.grid_width_ = 0;
    source.sdl_window_ = nullptr;
    source.title_ = "";
    source.children_.clear();
}

Window& Window::operator=(Window& source) {
    height_ = source.height_;
    width_ = source.width_;
    grid_height_ = source.grid_height_;
    grid_width_ = source.grid_width_;
    sdl_window_ = source.sdl_window_;
    title_ = source.title_;
    children_ = source.children_;

    source.height_ = 0;
    source.width_ = 0;
    source.grid_height_ = 0;
    source.grid_width_ = 0;
    source.sdl_window_ = nullptr;
    source.title_ = "";
    source.children_.clear();

    return *this;
}

Window::Window(Window&& source) {
    height_ = source.height_;
    width_ = source.width_;
    grid_height_ = source.grid_height_;
    grid_width_ = source.grid_width_;
    sdl_window_ = source.sdl_window_;
    title_ = source.title_;
    children_ = source.children_;

    source.height_ = 0;
    source.width_ = 0;
    source.grid_height_ = 0;
    source.grid_width_ = 0;
    source.sdl_window_ = nullptr;
    source.title_ = "";
    source.children_.clear();
}

Window& Window::operator=(Window&& source) {
    height_ = source.height_;
    width_ = source.width_;
    grid_height_ = source.grid_height_;
    grid_width_ = source.grid_width_;
    sdl_window_ = source.sdl_window_;
    title_ = source.title_;
    children_ = source.children_;

    source.height_ = 0;
    source.width_ = 0;
    source.grid_height_ = 0;
    source.grid_width_ = 0;
    source.sdl_window_ = nullptr;
    source.title_ = "";
    source.children_.clear();

    return *this;
}

SDL_Window* Window::get_sdl_window() const { 
    return sdl_window_; 
}

void Window::add_child(Sprite* sprite) {
    children_.push_back(sprite);
}

std::size_t Window::get_height() const {
    return height_;
}

std::size_t Window::get_width() const {
    return width_;
}

std::size_t Window::get_grid_height() const {
    return grid_height_;
}

std::size_t Window::get_grid_width() const {
    return grid_width_;
}

std::vector<Sprite*> Window::get_children() {
    return children_;
}

void Window::set_window_title(int fps, int score) {
    std::string new_title = 
        title_ + " FPS: " + std::to_string(fps) + " Score: " + std::to_string(score); 
    SDL_SetWindowTitle(sdl_window_, new_title.c_str());
}

void Window::remove_child(int index) {
    children_.erase(children_.begin() + index);
}