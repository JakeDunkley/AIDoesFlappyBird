#pragma once

#include <SFML/Graphics.hpp>

namespace shared {
    extern const float screen_width = 2560;
    extern const float screen_height = 1440;
    sf::RenderWindow* window;
    sf::Clock clock;
}