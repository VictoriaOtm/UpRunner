//
// Created by otm on 22.04.17.
//

#ifndef UPRUN_GAME_H
#define UPRUN_GAME_H

#include <SFML/Graphics.hpp>
#include "utils/config.h"
#include "object/entities/views/heroView.h"
#include "object/block/blockView/blockView.h"
#include "interface/gui/gui.h"
#include "interface/menu/newGameMenu.h"
#include "map/Map.h"
#include "map/mapView.h"
#include <SFML/Audio.hpp>

namespace game {
    class Game {
    public:
        Game();

        ~Game() noexcept = default;

        void run() throw(std::runtime_error);

    private:
        config _config;

        sf::RenderWindow _window;

        mapView _map;

        heroView _hero;

        gui _gui;

        sf::View _camera;

        game::menu::newGameMenu _newGameMenu;

        sf::Color _background;

        sf::Music mainTheme;

        sf::Music gameOver;

        bool _isGame = false;

        bool _isMenu = true;

        void updateWindow() noexcept;

        void updateGame(int time) noexcept;

        void drawWindow() noexcept;

        void eventDispatcher() noexcept;

    };
}


#endif //UPRUN_GAME_H