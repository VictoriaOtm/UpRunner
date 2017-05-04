//
// Created by otm on 02.05.17.
//

#ifndef UPRUN_MENU_H
#define UPRUN_MENU_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../utils/exceptions.h"
#include "../../utils/config.h"

namespace game {
    enum choice {
        newGame = 1,
        settings,
        quit
    };

    class menu {
    public:
        menu(sf::RenderWindow &window, config &cfg) throw(game::error::textureNotFound);

        ~menu() noexcept = default;

        void drawMenu();

        void updateMenu();

        void run();

        void eventDispatcher();

    private:
        sf::RenderWindow &_window;

        unsigned int _height;
        unsigned int _width;

        uint16_t _choice;

        bool _menu;

        sf::Texture _backgroundT;
        sf::Texture _quitT;
        sf::Texture _newGameT;
        sf::Texture _settingsT;

        sf::Sprite _background;
        sf::Sprite _quit;
        sf::Sprite _newGame;
        sf::Sprite _settings;
    };
}


#endif //UPRUN_MENU_H