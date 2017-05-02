//
// Created by otm on 22.04.17.
//

#include "gui.h"

game::gui::gui()
{
    if (_hpFillT.loadFromFile("./textures/hpFill.png")
        && _hpFrameT.loadFromFile("./textures/hpFrame.png")
        && _lifeT.loadFromFile("./textures/lifeIcon.png")
        && _coinT.loadFromFile("./textures/coin.png")) {

        _hpFill.setTexture(_hpFillT);
        _hpFrame.setTexture(_hpFrameT);
        _coin.setTexture(_coinT);
        _life.setTexture(_lifeT);

    } else throw game::error::textureNotFound("Texture not found");

    if (_font.loadFromFile("./interface/a_Alterna.ttf")){
        _lifesNum.setFont(_font);
        _coinsNum.setFont(_font);

        _lifesNum.setCharacterSize(28);
        _coinsNum.setCharacterSize(28);

        _lifesNum.setFillColor(sf::Color::White);
        _coinsNum.setFillColor(sf::Color::White);

    }
    else throw game::error::fontNotFound("Font not found");

}

void game::gui::draw(sf::RenderWindow &window) {
    window.draw(_hpFill);
    window.draw(_hpFrame);

    window.draw(_coin);
    window.draw(_life);

    window.draw(_lifesNum);
    window.draw(_coinsNum);
}

void game::gui::update(const hero& _hero) {
    _hpFill.setTextureRect(sf::Rect<int>(0, 0, _hero.getHp(), 50));

    _hpFill.setPosition(25, 25);
    _hpFrame.setPosition(25, 25);

    _life.setPosition(25, 95);
    _coin.setPosition(150, 95);

    _lifesNum.setPosition(92, 95);
    _coinsNum.setPosition(217, 95);

    _lifesNum.setString(std::to_string(_hero.getLifes()));
    _coinsNum.setString(std::to_string(_hero.getCoins()));

}

