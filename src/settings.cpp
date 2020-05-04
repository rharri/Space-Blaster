#include <fstream>
#include <sstream>
#include <regex>

#include "settings.h"

Settings::Settings() : 
    width_(640), 
    height_(640), 
    fps_(60), 
    ms_per_frame_(1000 / fps_),
    grid_height_(32),
    grid_width_(32) {}

Settings::Settings(const std::string& filename) {
    if (filename.empty()) {
        std::cout << "error: Invalid filename" << std::endl;
        default_settings();
        return;
    }

    std::ifstream input_file_stream{filename, std::ios_base::in};
    if (!input_file_stream) {
        std::cout << "error: Unable to read settings." << std::endl;
        std::cout << "error: Using defaults." << std::endl;
        default_settings();
    } else {
        // Read settings file (game.settings)      
        try {
            std::string line;
            std::stringstream ss;
            std::vector<int> values;
            while (std::getline(input_file_stream, line)) {
                ss.str(line);

                std::string label;
                std::string delim;
                int value;

                ss >> label >> delim >> value;

                values.push_back(value);
                ss.clear();
            }

            width_          = values[0]; 
            height_         = values[1]; 
            fps_            = values[2]; 
            ms_per_frame_   = values[3] / fps_;
            grid_height_    = values[4];
            grid_width_     = values[5];

        } catch(const std::exception& e) {
            std::cout << "error: Unable to read settings." << std::endl;
            std::cout << "error: Using defaults." << std::endl;
            default_settings();        
        }
    }    
}

void Settings::default_settings() {
    width_          = 640; 
    height_         = 640; 
    fps_            = 60; 
    ms_per_frame_   = 1000 / fps_;
    grid_height_    = 32;
    grid_width_     = 32;
}