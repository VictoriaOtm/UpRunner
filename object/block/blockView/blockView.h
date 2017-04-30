#ifndef UPRUN_BLOCKVIEW_H
#define UPRUN_BLOCKVIEW_H

#include <SFML/Graphics.hpp>
#include "../block.h"
#include "../../../utils/exceptions.h"

namespace game {

    enum blockSpritesFacing_row{
        NotUsed1, NotUsed2, NotUsed3, NotUsed4, NotUsed5, NotUsed6, Block, NotUsed8
    };
    enum blockSpritesFacing_col{
        NotUsed_1, NotUsed_2, NotUsed_3, NotUsed_4, NotUsed_5, NotUsed_6, Red, NotUsed_8,
        Gray, Brown, NotUsed_11, NotUsed_12, NotUsed_13
    };

    class blockView : public block {
    public:
        blockView() throw(game::error::textureNotFound);

        void draw(sf::RenderWindow &window);

    private:
        int _tileXSize = 128;
        int _tileYSize = 128;

        sf::Texture _texture;
        std::vector<std::vector<sf::Sprite>> _sprites;

        void parseTexture();

        sf::Sprite* _curSprite = nullptr;
    };
}


#endif //UPRUN_BLOCKVIEW_H