//
// Created by otm on 22.04.17.
//

#include "gui.h"
#include "../../map/mapView.h"

game::gui::gui(sf::RenderWindow &window) : window(window) {
    if (_hpFillT.loadFromFile("./textures/hpFill.png")
        && _hpFrameT.loadFromFile("./textures/hpFrame.png")
        && _lifeT.loadFromFile("./textures/lifeIcon.png")
        && _coinT.loadFromFile("./textures/coin.png")) {

        _hpFill.setTexture(_hpFillT);
        _hpFrame.setTexture(_hpFrameT);
        _coin.setTexture(_coinT);
        _life.setTexture(_lifeT);

    } else throw game::error::textureNotFound("Texture not found");

    if (_font.loadFromFile("./interface/a_Alterna.ttf")) {
        _lifesNum.setFont(_font);
        _coinsNum.setFont(_font);
        _level.setFont(_font);

        _lifesNum.setCharacterSize(28);
        _coinsNum.setCharacterSize(28);
        _level.setCharacterSize(28);

        _lifesNum.setColor(sf::Color::White);
        _coinsNum.setColor(sf::Color::White);
        _level.setColor(sf::Color::White);

    } else throw game::error::fontNotFound("Font not found");

}

void game::gui::draw() {
    window.draw(_hpFill);
    window.draw(_hpFrame);

    window.draw(_coin);
    window.draw(_life);

    window.draw(_lifesNum);
    window.draw(_coinsNum);
    window.draw(_level);
}

void game::gui::update(const hero &_hero, mapView &_map) {
    sf::Vector2f position =
            window.getView().getCenter() - sf::Vector2f(window.getView().getSize().x / 2, window.getView().getSize().y / 2);
    _hpFill.setTextureRect(sf::Rect<int>(0, 0, _hero.getHp(), 50));

    _hpFill.setPosition(position + sf::Vector2f(25, 25));
    _hpFrame.setPosition(position + sf::Vector2f(25, 25));

    _life.setPosition(position + sf::Vector2f(25, 95));
    _coin.setPosition(position + sf::Vector2f(150, 95));

    _lifesNum.setPosition(position + sf::Vector2f(92, 95));
    _coinsNum.setPosition(position + sf::Vector2f(217, 95));
    _level.setPosition(position + sf::Vector2f(25, 165));

    _lifesNum.setString(std::to_string(_hero.getLifes()));
    _coinsNum.setString(std::to_string(_hero.getCoins()));
    _level.setString(std::to_string(_map.getCurrLine() - 17));

}

