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
#include "interface/menu/menu.h"
#include "map/Map.h"

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

        blockView _block;

        gui _gui;

        menu _menu;

        Map _map;

        sf::Color _background;

        void updateWindow() noexcept;

        void updateGame(int time) noexcept;

        void drawWindow() noexcept;

        void eventDispatcher() noexcept;

    };
}


#endif //UPRUN_GAME_H