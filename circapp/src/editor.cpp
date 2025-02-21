#include "editor.h"


void Editor::handleEvent(const sf::Event& event) {
    if (event.is<sf::Event::Closed>()) {
        m_closed = true;
        // window.close();
    }
}

void Editor::draw(sf::RenderTarget& target) {
    target.clear(sf::Color::Magenta);
}

