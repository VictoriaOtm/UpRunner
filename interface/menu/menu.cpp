//
// Created by otm on 02.05.17.
//

#include <SFML/Window/Event.hpp>
#include "menu.h"

game::menu::menu(sf::RenderWindow &window, config &cfg) throw(game::error::textureNotFound)
        : _window(window), _height(cfg.getVideoMode().height), _width(cfg.getVideoMode().width),
          _choice(0), _menu(true) {
    if (_backgroundT.loadFromFile("./textures/menu.png")
        && _newGameT.loadFromFile("./textures/newGame.png")
        && _quitT.loadFromFile("./textures/quit.png")
        && _settingsT.loadFromFile("./textures/settings.png")) {

        _background.setTexture(_backgroundT);
        _newGame.setTexture(_newGameT);
        _settings.setTexture(_settingsT);
        _quit.setTexture(_quitT);
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::menu::drawMenu() {
    _window.clear(sf::Color::Black);
    _window.draw(_background);
    _window.draw(_newGame);
    _window.draw(_settings);
    _window.draw(_quit);

    _window.display();
}

void game::menu::updateMenu() {
    _background.setPosition(_width / 4, _height / 4);
    _newGame.setPosition(_width / 4 + 100, _height / 4 + 128);
    _settings.setPosition(_width / 4 + 100, _height / 4 + 173);
    _quit.setPosition(_width / 4 + 100, _height / 4 + 218);
}

void game::menu::run() {
    _menu = true;
    while (_menu) {
        eventDispatcher();
        updateMenu();
        drawMenu();
    }
}

void game::menu::eventDispatcher() {
    sf::Event event;

    while (_window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                _window.close();
                _menu = false;
                break;
            }

            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Key::Escape: {
                        _menu = false;
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