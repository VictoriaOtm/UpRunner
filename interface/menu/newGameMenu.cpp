//
// Created by otm on 02.05.17.
//

#include <SFML/Window/Event.hpp>
#include <iostream>
#include <SFML/Graphics/CircleShape.hpp>
#include "newGameMenu.h"

game::menu::newGameMenu::newGameMenu(sf::RenderWindow &window, config &cfg) throw(game::error::textureNotFound)
        : _window(window), _height(cfg.getVideoMode().height), _width(cfg.getVideoMode().width),
          _choice(0), _menu(true), _conMenu(false) {


    if (_backgroundT.loadFromFile("./textures/menu.png")
        && _newGameT.loadFromFile("./textures/newGame.png")
        && _quitT.loadFromFile("./textures/quit.png")
        && _settingsT.loadFromFile("./textures/settings.png")
        && _continueT.loadFromFile("./textures/continue.png")
        && _gameOverT.loadFromFile("./textures/gameover.png")) {

        _backgroundS.setTexture(_backgroundT);
        _newGame.setTexture(_newGameT);
        _settings.setTexture(_settingsT);
        _quit.setTexture(_quitT);
        _continue.setTexture(_continueT);
        _gameOver.setTexture(_gameOverT);

    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::menu::newGameMenu::drawGO() {
    _gameOver.setPosition(_position + sf::Vector2f(_width / 4, 406));
    _window.draw(_gameOver);
    _window.display();
}

void game::menu::newGameMenu::drawMenu() {
    _window.draw(_backgroundS);
    _window.draw(_newGame);
    _window.draw(_settings);
    _window.draw(_quit);

    if (_conMenu) {
        _window.draw(_continue);
    }

    _window.display();
}

void game::menu::newGameMenu::updateMenu() {
    uint16_t strHeight = 173;

    sf::Vector2f menuPos = _position + sf::Vector2f(_width / 4, _height / 4);

    _backgroundS.setPosition(menuPos);
    _newGame.setPosition(menuPos + sf::Vector2f(100, 128));
    if (_conMenu) {
        _continue.setPosition(menuPos + sf::Vector2f(100, strHeight));
        strHeight += 45;
    }
    _settings.setPosition(menuPos + sf::Vector2f(100, strHeight));
    strHeight += 45;
    _quit.setPosition(menuPos + sf::Vector2f(100, strHeight));
}

void game::menu::newGameMenu::runNew() {
    _position =
            _window.getView().getCenter() -
            sf::Vector2f(_window.getView().getSize().x / 2, _window.getView().getSize().y / 2);
    _menu = true;
    while (_menu) {
        updateMenu();
        drawMenu();
        eventDispatcher();
    }
}

void game::menu::newGameMenu::runContinue(bool _isGame) {
    _menu = false;
    _conMenu = true;

    while (_conMenu) {
        updateMenu();
        drawMenu();
        eventDispatcher();
    }

    _isGame = true;
}

void game::menu::newGameMenu::eventDispatcher() {
    sf::Event event;

    while (_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                _menu = false;
                _window.close();
                break;
            }

            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Key::Escape: {
                        if (!_menu && _conMenu) {
                            _conMenu = false;
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
                break;
            }


            case sf::Event::MouseMoved : {

                if (_newGame.getGlobalBounds().contains(_position + sf::Vector2f(sf::Mouse::getPosition(_window).x,
                                                                                 sf::Mouse::getPosition(_window).y))) {
                    _choice = game::menu::choice::newGame;
                } else if (_quit.getGlobalBounds().contains(_position + sf::Vector2f(sf::Mouse::getPosition(_window).x,
                                                            sf::Mouse::getPosition(_window).y))) {
                    _choice = game::menu::choice::quit;
                } else if (_settings.getGlobalBounds().contains(_position + sf::Vector2f(sf::Mouse::getPosition(_window).x,
                                                                sf::Mouse::getPosition(_window).y))) {
                    _choice = game::menu::choice::settings;
                } else if (_continue.getGlobalBounds().contains(_position + sf::Vector2f(sf::Mouse::getPosition(_window).x,
                                                                sf::Mouse::getPosition(_window).y))) {
                    _choice = game::menu::choice::continueGame;
                } else {
                    _choice = game::menu::choice::none;
                }
                break;
            }

            default: {
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            switch (_choice) {
                case game::menu::choice::newGame: {
                    _menu = false;

                    break;
                }
                case game::menu::choice::settings: {
                    break;
                }

                case game::menu::choice::continueGame : {
                    _conMenu = false;
                    break;
                }

                case game::menu::choice::quit: {
                    _menu = false;
                    _window.close();
                    break;
                }
                default: {
                    break;
                }
            }
        }
    }
}
