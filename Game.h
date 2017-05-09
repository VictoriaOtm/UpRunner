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

namespace game {
    class Game {
    public:
        Game();

        ~Game() noexcept = default;

        void run() throw(std::runtime_error);

    private:
        config _config;

        sf::RenderWindow _window;

        heroView _hero;

        mapView _map;

        gui _gui;

        game::menu::newGameMenu _newGameMenu;

        sf::Color _background;

        bool _isGame = false;

        bool _isMenu = true;

        void updateWindow() noexcept;

        void updateGame(int time) noexcept;

        void drawWindow() noexcept;

        void eventDispatcher() noexcept;

    };
}


#endif //UPRUN_GAME_H