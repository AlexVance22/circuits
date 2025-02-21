#include "player.h"
#include <iostream>


void Player::update(const float dt) {
    std::cout << "fps: " << 1.f / dt << "\n";
}

void Player::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        m_closed = true;
        // window.close();
    }
}

void Player::draw(sf::RenderTarget& target) {
    target.clear(sf::Color::Magenta);
}

