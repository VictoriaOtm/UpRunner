//
// Created by otm on 02.05.17.
//

#include <SFML/Window/Event.hpp>
#include "menu.h"

game::menu::menu() throw(game::error::textureNotFound) : _menu(true), _choice(0) {
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

const bool game::menu::isMenu() const {
    return _menu;
}

void game::menu::drawMenu(sf::RenderWindow &window) {
    window.clear(sf::Color::Transparent);
    if(_menu){
        window.draw(_background);
        window.draw(_newGame);
        window.draw(_settings);
        window.draw(_quit);

        window.display();
    }
}

void game::menu::updateMenu() {
    _background.setPosition(_width / 4, _height / 4);
    _newGame.setPosition(_width / 4 + 100, _height / 4 + 128);
    _settings.setPosition(_width / 4 + 100, _height / 4 + 173);
    _quit.setPosition(_width / 4 + 100, _height / 4 + 218);
}

void game::menu::runMenu(sf::RenderWindow &window) {
    _menu = true;
    while (_menu) {
        eventDispatcher(window);
        updateMenu();
        drawMenu(window);
    }
}

void game::menu::eventDispatcher(sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                window.close();
                _menu = false;
                break;
            }

            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                    case sf::Keyboard::Key::Escape: {
                        _menu = false;
                        break;
                    }
                    default:{
                        break;
                    }
                }
            }

            default: {
                break;
            }
        }
    }
}