//
// Created by otm on 22.04.17.
//


#ifndef UPRUN_GUI_H
#define UPRUN_GUI_H

#include "../../utils/config.h"
#include "../../object/entities/hero.h"
#include <SFML/Graphics.hpp>
namespace game{
    class gui {
    public:
        gui();

        void draw(sf::RenderWindow &window);

        void update(const hero& _hero);

    private:
        sf::Texture _hpFillT;
        sf::Texture _hpFrameT;
        sf::Texture _coinT;
        sf::Texture _lifeT;

        sf::Sprite _hpFill;
        sf::Sprite _hpFrame;
        sf::Sprite _coin;
        sf::Sprite _life;

        sf::Text _lifesNum;
        sf::Text _coinsNum;

        sf::Font _font;

        float height, width;

//        sf::Text points;
//        sf::Font font;
    };
};


#endif //UPRUN_GUI_H
