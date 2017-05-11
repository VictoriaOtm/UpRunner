//
// Created by otm on 22.04.17.
//


#ifndef UPRUN_GUI_H
#define UPRUN_GUI_H

#include "../../utils/config.h"
#include "../../object/entities/hero.h"
#include "../../map/mapView.h"
#include <SFML/Graphics.hpp>
namespace game{
    class gui {
    public:
        gui(sf::RenderWindow &window);

        void draw();

        void update(const hero &_hero, mapView &_map);

    private:
        sf::RenderWindow &window;

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
        sf::Text _level;

        sf::Font _font;

        float height, width;

//        sf::Text points;
//        sf::Font font;
    };
};


#endif //UPRUN_GUI_H
