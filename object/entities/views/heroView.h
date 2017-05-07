//
// Created by otm on 22.04.17.
//

#ifndef UPRUN_HEROVIEW_H
#define UPRUN_HEROVIEW_H

#include <SFML/Graphics.hpp>
#include <boost/circular_buffer.hpp>
#include "../hero.h"
#include "../../../utils/exceptions.h"

namespace game {
    enum heroSpritesFacing {
        Ladder, Left, Right
    };

    enum movement {
        left = -1,
        right = 1,
        up = -1,
        down = 1,
    };

    class heroView : public hero {
    public:
        heroView() throw(game::error::textureNotFound);

        void update(int time,const boost::circular_buffer<std::vector<char>>& _map);

        void draw(sf::RenderWindow &window);

        void changeMovementVec(const int xRotation, const int yRotation);

    private:
        void parseTexture();

        void collisionCheck(int time, const boost::circular_buffer<std::vector<char>>& _map);

        void alterMovementVec();

        void gravityFall(int time);

        int _tileXSize = 128;
        int _tileYSize = 104;

        sf::Texture _texture;

        std::vector<std::vector<sf::Sprite>> _sprites;

        sf::Vector2i _movementVector = sf::Vector2i(0, 0);

        sf::Sprite *_curSprite = nullptr;

        uint8_t _curFacing = heroSpritesFacing::Right;

        float _curFrame = 0;

        const double _speedFactor = 50;

        bool _isFalling;
        bool _isLadder;

    };
}

#endif //UPRUN_HEROVIEW_H
