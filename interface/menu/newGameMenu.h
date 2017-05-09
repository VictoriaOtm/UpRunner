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
    namespace menu {
        enum choice {
            none,
            newGame,
            continueGame,
            settings,
            quit
        };

        class newGameMenu {
        public:
            newGameMenu(sf::RenderWindow &window, config &cfg) throw(game::error::textureNotFound);

            ~newGameMenu() noexcept = default;

            void drawMenu();

            void drawGO();

            void updateMenu();

            void runNew();

            void runContinue(bool _isGame);

            void eventDispatcher();

        private:
            sf::RenderWindow &_window;

            unsigned int _height;
            unsigned int _width;

            uint16_t _choice;

            bool _menu;
            bool _conMenu;

            sf::Texture _backgroundT;
            sf::Texture _quitT;
            sf::Texture _newGameT;
            sf::Texture _settingsT;
            sf::Texture _continueT;
            sf::Texture _gameOverT;

            sf::Sprite _backgroundS;
            sf::Sprite _quit;
            sf::Sprite _newGame;
            sf::Sprite _settings;
            sf::Sprite _continue;
            sf::Sprite _gameOver;
        };
    }
}


#endif //UPRUN_MENU_H