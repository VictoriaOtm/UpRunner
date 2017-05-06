//
// Created by otm on 22.04.17.
//

#include <iostream>
#include "Game.h"

game::Game::Game() :
        _window(_config.getVideoMode(), _config.getWinTitle(), _config.getStyle()), _menu(_window, _config), _background(153, 210, 215) {
    _window.setKeyRepeatEnabled(false);
    _window.setFramerateLimit(_config.getMenuFPSLimit());
    _window.setVerticalSyncEnabled(_config.getVSync());
}

void game::Game::run() throw(std::runtime_error) {
    _window.clear(_background);
    _menu.run();

    sf::Clock clock;
    sf::Time elapsed;

//    for (std::vector<char> line : _map.getBuffer()){
//        for (char block : line){
//            std::cout << block << ' ';
//        }
//        std::cout << std::endl;
//    }

    while (_window.isOpen()) {
        eventDispatcher();
        elapsed = clock.restart();
        updateWindow();
        updateGame(elapsed.asMilliseconds());
    }

}

void game::Game::updateWindow() noexcept {
    _window.clear(_background);
    drawWindow();

    _window.display();
}

void game::Game::drawWindow() noexcept {
    for(int i = 0; i < 16; ++i){
        for(int j = 0; j < 12; ++j){
            _block.draw(_window, _map.getBuffer()[i][j], i, j);
        }
    }
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
                        _menu.run();
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
    _hero.update(time, _map.getBuffer());
    _gui.update(_hero);
    //mapUpdate ...
    return;
}

