//
// Created by otm on 22.04.17.
//

#include <iostream>
#include "Game.h"

game::Game::Game() :
        _window(_config.getVideoMode(), _config.getWinTitle(), _config.getStyle()), isGame(false){
    _window.setKeyRepeatEnabled(false);
    _window.setFramerateLimit(_config.getMenuFPSLimit());
    _window.setVerticalSyncEnabled(_config.getVSync());
}

void game::Game::run() throw(std::runtime_error) {
    sf::Clock clock;
    sf::Time elapsed;

    while (_window.isOpen()) {
        elapsed = clock.restart();

        _menu.runMenu(_window);

        eventDispatcher();
        updateGame(elapsed.asMilliseconds());
        updateWindow();
    }

}

void game::Game::updateWindow() noexcept {
//    sf::RectangleShape floor(sf::Vector2f(400, 300));
//    floor.setPosition(0, 300);
//    floor.setFillColor(sf::Color(255, 255, 250));

    _window.clear(sf::Color::Black);
    drawWindow();

//    _window.draw(floor);
    _window.display();
}

void game::Game::drawWindow() noexcept {
    //create map
    _block.draw(_window); //
    _hero.draw(_window);
    _gui.draw(_window);
}

void game::Game::eventDispatcher() noexcept {
    sf::Event event;

    while (_window.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed: {
                _window.close();
                break;
            }

            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Key::Left: {
                        _hero.changeMovementVec(game::movement::left, 0);
                        break;
                    }

                    case sf::Keyboard::Key::Right: {
                        _hero.changeMovementVec(game::movement::right, 0);
                        break;
                    }

                    case sf::Keyboard::Key::Up: {
                        _hero.increaseHp(30);
                        _hero.changeMovementVec(0, game::movement::up);
                        break;
                    }

                    case sf::Keyboard::Key::Down: {
                        _hero.decreaseHp(30);
                        _hero.changeMovementVec(0, game::movement::down);
                        break;
                    }

                    case sf::Keyboard::Key::Space: {
                        _hero.jump();
                        break;
                    }

                    case sf::Keyboard::Key::Escape: {
                        _menu.runMenu(_window);
                        break;
                    }

                    default: {
                        break;
                    }
                }
                break;
            }

            case sf::Event::KeyReleased: {
                switch (event.key.code) {
                    case sf::Keyboard::Key::Left: {
                        _hero.changeMovementVec(game::movement::right, 0);
                        break;
                    }

                    case sf::Keyboard::Key::Right: {
                        _hero.changeMovementVec(game::movement::left, 0);
                        break;
                    }

                    case sf::Keyboard::Key::Up: {
                        _hero.changeMovementVec(0, game::movement::down);
                        break;
                    }

                    case sf::Keyboard::Key::Down: {
                        _hero.changeMovementVec(0, game::movement::up);
                        break;
                    }

                    case sf::Keyboard::Key::Space: {
                        break;
                    }

                    default: {
                        break;
                    }
                }
                break;
            }

            default: {
                break;
            }
        }
    }
}

void game::Game::updateGame(int time) noexcept {
    _hero.update(time);
    _gui.update(_hero);
    _block.update();
    //mapUpdate ...
    return;
}
