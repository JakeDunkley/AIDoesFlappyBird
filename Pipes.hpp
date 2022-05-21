#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Shared.hpp"

class Pipe {
private:
    static constexpr float width = 80.0f;
    static constexpr float spacing = 120.0f;
    static constexpr float speed = 0.1f;

    float position;     // x-position of pipe pair.
    float gapY;         // Position of gap between pipes.
    bool active;        // Flag to determine if pipe pair is active in simulation.

    sf::RectangleShape pipeTop, pipeBot;

public:
    Pipe() {
        position = shared::screen_width;
        gapY = ((std::rand() % RAND_MAX) * (shared::screen_width * 0.5f) + (shared::screen_width * 0.25f)) - (spacing * 0.5f);
        active = false;

        pipeTop.setSize(sf::Vector2f(width, gapY));
        pipeBot.setSize(sf::Vector2f(width, shared::screen_height - gapY + (spacing * 0.5f)));
        pipeTop.setPosition(position, pipeTop.getPosition().y);
        pipeBot.setPosition(position, pipeBot.getPosition().y);
        pipeTop.setFillColor(sf::Color::Green);
        pipeBot.setFillColor(sf::Color::Green);
    }

    bool isActive() const {
        return active;
    }

    void flagActive(const bool& flag) {
        active = flag;
    }

    void reset() {
        position = shared::screen_width;
        gapY = ((std::rand() % RAND_MAX) * (shared::screen_width * 0.5f) + (shared::screen_width * 0.25f)) - (spacing * 0.5f);
    }

    void update() {
        if (active && position + width < 0) {
            active = false;
            reset();
        }

        if (active) {
            position -= speed;
            pipeTop.setPosition(position, pipeTop.getPosition().y);
            pipeBot.setPosition(position, pipeBot.getPosition().y);
        }
    }

    void draw() {
        shared::window->draw(pipeTop);
        shared::window->draw(pipeBot);
    }
};

class PipePool {
private:
    static constexpr float spawnRate = 1.0f;

    std::vector<Pipe*> pipes;
    float timeOfLastSpawn;

public:
    explicit PipePool(const int& size) {
        for (int i = 0; i < size; i++) {
            pipes.push_back(new Pipe());
        }

        timeOfLastSpawn = shared::clock.getElapsedTime().asSeconds();
    }

    std::vector<Pipe*> getAllActive() const {
        std::vector<Pipe*> toReturn;

        for (Pipe* p : pipes) {
            if (p->isActive()) toReturn.push_back(p);
        }

        return toReturn;
    }

    Pipe* getAvailable() const {
        for (Pipe* p : pipes) {
            if (!p->isActive()) return p;
        }

        return nullptr;
    }

    void spawnCheck() {
        if (timeOfLastSpawn < shared::clock.getElapsedTime().asSeconds() - spawnRate) {
            getAvailable()->flagActive(true);
            timeOfLastSpawn = shared::clock.getElapsedTime().asSeconds();
        }
    }

    void update() {
        for (Pipe* p : pipes) {
            p->update();
        }

        spawnCheck();
    }

    void draw() {
        for (Pipe* p : pipes) {
            if (p->isActive()) p->draw();
        }
    }

    void draw_debug() {
        for (int i = 0; i < pipes.size(); i++) {
            sf::RectangleShape r(sf::Vector2f (20.0f, 20.0f));
            r.setPosition(10.0f, (float) i * 10.0f + 10.0f);
            pipes[i]->isActive() ? r.setFillColor(sf::Color::White) : r.setFillColor(sf::Color::Blue);
            shared::window->draw(r);
        }
    }
};