//
// Created by root on 07.05.17.
//

#ifndef UPRUN_MAPVIEW_H
#define UPRUN_MAPVIEW_H


#include <SFML/Graphics/Sprite.hpp>
#include "Map.h"
#include "../object/block/blockView/blockView.h"

struct Block{
    sf::Sprite blockSprite;
    uint8_t blockType;
};

namespace game {
    class mapView : game::Map {
    public:
        mapView(sf::RenderWindow &window);

        mapView(const mapView &rhs);

        ~mapView() noexcept override = default;

        void draw();

        void update();

        const uint16_t tileHeight() const;

        const uint16_t tileWidth() const;

        boost::circular_buffer<std::vector<Block>> blocks;
    private:
        sf::Texture _blocksTexture;
        sf::RenderWindow &_window;

        const uint16_t _tileHeight = 64;
        const uint16_t _tileWidth = 64;
    };
}


#endif //UPRUN_MAPVIEW_H