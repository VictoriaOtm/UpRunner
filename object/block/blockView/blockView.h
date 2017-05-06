#ifndef UPRUN_BLOCKVIEW_H
#define UPRUN_BLOCKVIEW_H

#include <SFML/Graphics.hpp>
#include "../block.h"
#include "../../../utils/exceptions.h"
#include "../../../map/Map.h"

namespace game {

    //enum blockType

    class blockView : public Map {
    public:
        blockView() throw(game::error::textureNotFound);

        void draw(sf::RenderWindow &window, char, int, int);

        void update();

    private:

        sf::Texture _blockT;

        int _tileXSize = 128;
        int _tileYSize = 128;

        std::vector<std::vector<sf::Sprite>> _sprites;

        void parseTexture();

        sf::Sprite* _curSprite = nullptr;
    };
}


#endif //UPRUN_BLOCKVIEW_H