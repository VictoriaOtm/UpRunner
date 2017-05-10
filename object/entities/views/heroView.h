//
// Created by otm on 22.04.17.
//

#ifndef UPRUN_HEROVIEW_H
#define UPRUN_HEROVIEW_H

#include <SFML/Graphics.hpp>
#include <boost/circular_buffer.hpp>
#include "../hero.h"
#include "../../../utils/exceptions.h"
#include "../../../map/mapView.h"


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

    enum collision {
        colUpLeft,
        colUp,
        colUpRight,
        colLeft,
        colCenter,
        colRight,
        colDownLeft,
        colDown,
        colDownRight
    };

    class heroView : public hero {
    public:
        heroView(sf::RenderWindow &window) throw(game::error::textureNotFound);

        void update(int time, const game::mapView& map);

        void draw();

        void changeMovementVec(const int xRotation, const int yRotation);

        bool _gameOver;

        void setHeroToPoint(const sf::Vector2f point);

    private:
        void parseTexture();

        void collisionCheck(int time, const game::mapView& Map);

        sf::FloatRect getNextFrame(int time);

        void resolveCollision(const uint8_t collisionFrom, const Block &collidedBlock);

        void affectCollision(const uint8_t collisionFrom, const Block &collidedBlock);

        void alterMovementVec();

        void gravityFall(int time);

        float _tileXSize = 94;
        float _tileYSize = 104;

        sf::Texture _texture;

        std::vector<std::vector<sf::Sprite>> _sprites;

        sf::Vector2i _movementVector = sf::Vector2i(0, 0);

        sf::Sprite *_curSprite = nullptr;

        uint8_t _curFacing = heroSpritesFacing::Right;

        sf::RenderWindow &_window;

        float _curFrame = 0;

        float _speedOnMap = 0.5f;

        const double _speedFactor = 50;

        bool _isFalling;
        bool _isLadder;

        bool checkBounds(sf::FloatRect &heroNextRect);
    };
}

#endif //UPRUN_HEROVIEW_H
