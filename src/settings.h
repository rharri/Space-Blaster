#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <string>

class Settings {
    friend class Game;
    
public:
    Settings();
    Settings(const std::string& filename);

private:
    void default_settings();
    std::size_t width_;
    std::size_t height_;
    std::size_t fps_;
    std::size_t ms_per_frame_;
    std::size_t grid_height_;
    std::size_t grid_width_;
};

#endif