//
// Created by otm on 02.05.17.
//

#ifndef UPRUN_MENU_H
#define UPRUN_MENU_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../utils/exceptions.h"

namespace game{
    enum choice{
        newGame = 1,
        settings,
        quit
    };

    class menu {
    public:
        menu() throw(game::error::textureNotFound);

        ~menu() noexcept = default;

        const bool isMenu() const;

        void drawMenu(sf::RenderWindow &window);

        void updateMenu();

        void runMenu(sf::RenderWindow &window);

        void eventDispatcher(sf::RenderWindow &window);

    private:
        sf::Texture _backgroundT;
        sf::Texture _quitT;
        sf::Texture _newGameT;
        sf::Texture _settingsT;

        sf::Sprite _background;
        sf::Sprite _quit;
        sf::Sprite _newGame;
        sf::Sprite _settings;

        uint16_t _choice;
        const uint16_t _height = 960;
        const uint16_t _width = 832;

        bool _menu;

    };
}



#endif //UPRUN_MENU_H
