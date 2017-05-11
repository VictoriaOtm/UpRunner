//
// Created by otm on 22.04.17.
//

#include <iostream>
#include "Game.h"

game::Game::Game() :
        _window(_config.getVideoMode(), _config.getWinTitle(), _config.getStyle()),
        _map(_window),
        _hero(_window),
        _gui(_window),
        _newGameMenu(_window, _config), _background(153, 210, 215) {

    _camera.setSize(_config.getVideoMode().width, _config.getVideoMode().height);
    _camera.setCenter(_config.getVideoMode().width / 2, _config.getVideoMode().height / 2 + 3 * _map.tileHeight());
    _window.setView(_camera);
    _window.setKeyRepeatEnabled(false);
    _window.setFramerateLimit(_config.getMenuFPSLimit());
    _window.setVerticalSyncEnabled(_config.getVSync());

}


void game::Game::run() throw(std::runtime_error) {
    sf::Clock clock;
    sf::Time elapsed;
    _window.clear(_background);

    _hero.setHeroToPoint(_map.startingPoint());

    while (_window.isOpen()) {
        if (_isGame) {
            if (!_hero._gameOver) {
                elapsed = clock.restart();
                updateWindow();
                updateGame(elapsed.asMilliseconds());
            } else {
                _window.clear(_background);
                _newGameMenu.drawGO();
            }
            eventDispatcher();
        } else if (_isMenu) {
            _newGameMenu.runNew();
            _isMenu = false;
            _isGame = true;
        }
    }

}

void game::Game::updateWindow() noexcept {
    _window.clear(_background);
    drawWindow();

    _window.display();
}

void game::Game::drawWindow() noexcept {
    _map.draw();
    _hero.draw();
    _gui.draw();
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
                if (!_hero._gameOver) {
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
                            _hero.changeMovementVec(0, game::movement::up);
                            break;
                        }

                        case sf::Keyboard::Key::Down: {
                            _hero.changeMovementVec(0, game::movement::down);
                            break;
                        }

                        case sf::Keyboard::Key::Space: {
                            _hero.jump();
                            break;
                        }

                        case sf::Keyboard::Key::Escape: {
                            _newGameMenu.runContinue(_isGame);
                            break;
                        }

                        default: {
                            break;
                        }
                    }
                }
                break;
            }

            case sf::Event::KeyReleased: {
                if (!_hero._gameOver) {
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
    _map.update();
    _hero.update(time, _map);
    _gui.update(_hero, _map);
    return;
}
