#include <SFML/Graphics.hpp>
#include <math.h>
#include "Shared.hpp"
#include "Pipes.hpp"

using shared::window;

int main() {
    window = new sf::RenderWindow(sf::VideoMode(shared::screen_width, shared::screen_height), "Flappy Bird");

    sf::CircleShape shape;
    shape.setRadius(40.f);
    shape.setPosition((shared::screen_width / 2.f) - 40.0f, (shared::screen_height / 2.f) - 40.0f);
    shape.setFillColor(sf::Color::Cyan);
    Pipe p(10.0f);

    while (window->isOpen()) {

        sf::Event event;

        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(shape);
        p.draw();
        window->display();
    }
}