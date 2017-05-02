#ifndef UPRUN_BLOCKVIEW_H
#define UPRUN_BLOCKVIEW_H

#include <SFML/Graphics.hpp>
#include "../block.h"
#include "../../../utils/exceptions.h"

namespace game {

    enum blockSpritesFacing_row{
        Block
    };

    class blockView : public block {
    public:
        blockView() throw(game::error::textureNotFound);

        void draw(sf::RenderWindow &window);

        void update();

    private:

        sf::Texture _blockT;

        sf::Sprite _block;
    };
}


#endif //UPRUN_BLOCKVIEW_H