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

    void breakBlock(){
        switch (blockType){
            case game::blockType::collapsingFloor : {
                blockType = game::blockType::collFloor;
                blockSprite.setTextureRect(sf::IntRect(game::blockType::collFloor, 0, 128, 128));
                break;
            }

            case game::blockType::collFloor: {
                blockType = game::blockType::empty;
                blockSprite.setTextureRect(sf::IntRect(game::blockType::empty, 0, 128, 128));
                break;
            }

            default:{
                break;
            }
        }
    }

    void collect(){
        if (blockType == game::blockType::coin){
            blockType = game::blockType::empty;
            blockSprite.setTextureRect(sf::IntRect(game::blockType::empty, 0, 128, 128));
        }
    }
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

        sf::Texture _coinTexture;

        const uint16_t _tileHeight = 64;
        const uint16_t _tileWidth = 64;

        float _speed = 0.5f;

    };
}


#endif //UPRUN_MAPVIEW_H