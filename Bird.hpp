#pragma once

#include <SFML/Graphics.hpp>
#include "Shared.hpp"

class Bird {
private:
    static constexpr float jumpAcc = -0.02f;
    static constexpr float gravAccel = 0.001f;
    static constexpr float maxVelUp = -0.5f;
    static constexpr float radius = 40.0f;

    sf::Vector2f position;
    float velocity, acceleration;

    sf::CircleShape birdBody;

public:
    Bird() {
        position = sf::Vector2f(shared::screen_width * 0.33f, shared::screen_height * 0.5f);

        velocity = 0.0f;
        acceleration = 0.0f;

        birdBody.setRadius(radius);
        birdBody.setPosition(position);
        birdBody.setFillColor(sf::Color::Red);
    }

    void update() {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            acceleration += jumpAcc;
        }

        acceleration += gravAccel;
        velocity += acceleration;
        if (velocity < maxVelUp) velocity = maxVelUp;
        position = sf::Vector2f(position.x, position.y + velocity);
        acceleration = 0.0f;
    }

    void draw() {
        birdBody.setPosition(position);
        shared::window->draw(birdBody);
    }
};