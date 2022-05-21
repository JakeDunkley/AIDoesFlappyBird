#pragma once

#include <SFML/Graphics.hpp>

namespace shared {
    extern const float screen_width = 1440;
    extern const float screen_height = 1440;
    sf::RenderWindow* window;
    sf::Clock clock;
}