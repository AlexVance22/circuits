#include <SFML/Graphics.hpp>
#include "player.h"
#include "editor.h"


enum class AppState {
    Edit,
    Play,
};


int main() {
    auto window = sf::RenderWindow(sf::VideoMode({ 800, 800 }), "Circuits", sf::Style::Default);
    window.setVerticalSyncEnabled(true);
    auto clock = sf::Clock();

    auto state = AppState::Edit;
    auto editor = Editor();
    auto player = Player();

    while (window.isOpen()) {
        while (state == AppState::Edit) {
            while (auto event = window.waitEvent()) {
                editor.handleEvent(*event);
                editor.draw(window);
                window.display();

                if (editor.closed()) {
                    window.close();
                    return 0;
                }
            }
        }

        clock.reset();
        while (state == AppState::Play) {
            const float dt = clock.restart().asSeconds();

            while (auto event = window.pollEvent()) {
                player.handleEvent(*event);
            }

            player.update(dt);
            player.draw(window);
            window.display();

            if (player.closed()) {
                window.close();
                return 0;
            }
        }
    }
}

