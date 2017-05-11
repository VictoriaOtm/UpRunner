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

                blockSprite.setTextureRect(sf::IntRect(game::blockType::collFloor * 128 , 0, 128, 128));
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

    void collectCoin(){
        if (blockType == game::blockType::coin){
            blockType = game::blockType::empty;
            blockSprite.setTextureRect(sf::IntRect(game::blockType::empty, 0, 128,128));
        }
    }
};

namespace game {
    class mapView : public game::Map {
    public:
        mapView(sf::RenderWindow &window);

        mapView(const mapView &rhs);

        ~mapView() noexcept override = default;

        void draw();

        void update();

        const float tileHeight() const;

        const float tileWidth() const;

        sf::Vector2f startingPoint();


        boost::circular_buffer<std::vector<Block>> blocks;
    private:
        sf::Texture _blocksTexture;
        sf::RenderWindow &_window;

        sf::Texture _coinTexture;

        float _tileHeight = 128;
        float _tileWidth = 128;

        float _speed = 0.5f;

    };
}


#endif //UPRUN_MAPVIEW_H