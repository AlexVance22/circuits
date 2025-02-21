#pragma once
#include <SFML/Graphics.hpp>


class Player {
private:
    bool m_closed = false;

public:
    bool closed() const { return m_closed; }

    void update(const float dt);
    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target);
};

