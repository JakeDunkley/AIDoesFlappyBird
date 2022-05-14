#pragma once

#include <SFML/Graphics.hpp>
#include "Shared.hpp"

class Pipe {
private:
    sf::RectangleShape topPipe, botPipe;
    sf::Vector2f coords;
    float offsetY;
    bool active;

public:
    static constexpr float width = 20.0f;
    static constexpr float spacing = 10.0f;
    static constexpr float speed = 1.5f;
    static constexpr float offsetYRange = 4.0f * width;

    explicit Pipe(const float& x) {
        coords = sf::Vector2f(x, 0.0f);
        this->offsetY = std::rand() % (int) offsetYRange;
        active = false;

        topPipe.setSize(sf::Vector2f(width, offsetY));
        botPipe.setSize(sf::Vector2f(width, shared::screen_height - (offsetY + spacing)));
        topPipe.setPosition(coords);
        botPipe.setPosition(sf::Vector2f(coords.x, offsetY + spacing));
        topPipe.setFillColor(sf::Color::Green);
        botPipe.setFillColor(sf::Color::Green);
    }

    void draw() {
        shared::window->draw(topPipe);
        shared::window->draw(botPipe);
    }

    sf::Vector2f getCoords() const {
        return coords;
    }

    float getOffsetY() const {
        return offsetY;
    }

    bool isActive() const {
        return active;
    }

    void flagActive(bool flag) {
        active = flag;
    }
};