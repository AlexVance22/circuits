#pragma once
#include <SFML/Graphics.hpp>


class Editor {
private:
    bool m_closed = false;

public:
    bool closed() const { return m_closed; }

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target);
};

