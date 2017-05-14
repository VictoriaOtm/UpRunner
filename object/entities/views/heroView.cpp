//
// Created by otm on 22.04.17.
//

#include <math.h>
#include "heroView.h"

game::heroView::heroView(sf::RenderWindow &window) throw(game::error::textureNotFound): _gameOver(false),
                                                                                        _window(window),
                                                                                        _isFalling(true),
                                                                                        _isLadder(false) {
    if (_texture.loadFromFile("./textures/heroTS1.png")) {
        parseTexture();

    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::heroView::update(int time, const game::mapView &map) {
    _position.y += _speedOnMap;

    collisionCheck(time, map);
    gravityFall(time);

    switch (_movementVector.x) {
        case game::movement::left: {
            if (!_collision.left) {
                alterX(_xSpeed * time * game::movement::left / _speedFactor);
            }
            break;
        }

        case game::movement::right: {
            if (!_collision.right) {
                alterX(_xSpeed * time * game::movement::right / _speedFactor);
            }
            break;
        }

        default: {
            break;
        }
    }

    //перепишется в зависимости от лестниц
    if (_isLadder) {
        switch (_movementVector.y) {
            case game::movement::up: {
                alterY(_xSpeed * time * game::movement::up / _speedFactor);
                break;
            }

            case game::movement::down: {
                alterY(_xSpeed * time * game::movement::down / _speedFactor);
                break;
            }

            default: {
                break;
            }
        }
    }

    if (_movementVector.x != 0) {
        _curFrame += time / 80.d;
        _curFrame >= 3 ? _curFrame = 0 : _curFrame;
    } else {
        _curFrame = 0;
    }

    _collision.reset();
    _isLadder = false;

}

void game::heroView::draw() {
    switch (_movementVector.x) {
        case game::movement::left : {
            _curFacing = game::heroSpritesFacing::Left;
            break;
        }

        case game::movement::right : {
            _curFacing = game::heroSpritesFacing::Right;
            break;
        }

        default: {

            break;
        }
    }

    switch (_movementVector.y) {
        case game::movement::up : {
            _curFacing = game::heroSpritesFacing::Ladder;
            break;
        }

        case game::movement::down : {
            _curFacing = game::heroSpritesFacing::Ladder;
            break;
        }

        default: {
            break;
        }
    }
    _curSprite = &_sprites[_curFacing][_curFrame];

    _curSprite->setPosition(getX(), getY());
    _window.draw(*_curSprite);
}

void game::heroView::parseTexture() {
    float scaleParameterH = static_cast<float>(_window.getSize().y) / (float)_window.getSize().y;
    float scaleParameterW = static_cast<float>(_window.getSize().x) / (float)_window.getSize().x;

    _sprites.resize(3);

    for (int row = 0; row < 3; row++) {
        _sprites[row].resize(3, sf::Sprite(_texture));

        for (int col = 0; col < 3; col++) {
            _sprites[row][col].setTextureRect(sf::IntRect(col * _tileXSize, row * _tileYSize, _tileXSize, _tileYSize));
            _sprites[row][col].setScale(scaleParameterW, scaleParameterH);
        }
    }

    _tileXSize *= scaleParameterW;
    _tileYSize *= scaleParameterH;

    _curSprite = &_sprites[game::heroSpritesFacing::Right][0];
}

void game::heroView::changeMovementVec(const int xRotation, const int yRotation) {
    _movementVector.x += xRotation;
    _movementVector.y += yRotation;
}

sf::FloatRect game::heroView::getNextFrame(int time) {
    sf::FloatRect heroNextRect = _curSprite->getGlobalBounds();
    heroNextRect.top += _ySpeed * time / _speedFactor;

    switch (_movementVector.x) {
        case game::movement::left: {
            heroNextRect.left += _xSpeed * time * game::movement::left / _speedFactor;
            break;
        }

        case game::movement::right: {
            heroNextRect.left += _xSpeed * time * game::movement::right / _speedFactor;
            break;
        }

        default: {
            break;
        }
    }
    return heroNextRect;
}

void game::heroView::resolveCollision(const uint8_t collisionFrom, const Block &collidedBlock) {
    if (collidedBlock.blockType == game::blockType::ladder) {
        _isLadder = true;
    } else {
        sf::FloatRect blockBounds = collidedBlock.blockSprite.getGlobalBounds();

        switch (collisionFrom) {
            case game::collision::colUp: {
                _collision.up = true;
                _position.y = blockBounds.top + blockBounds.height;
                break;
            }

            case game::collision::colLeft: {
                _collision.left = true;
                _position.x = blockBounds.left + blockBounds.width;
                break;
            }

            case game::collision::colDown: {
                _collision.down = true;
                _position.y = blockBounds.top - _tileYSize;
                break;
            }

            case game::collision::colRight: {
                _collision.right = true;
                _position.x = blockBounds.left - _tileXSize;
                break;
            }

            case game::collision::colUpLeft : {
                _collision.left = true;
                break;
            }

            case game::collision::colUpRight: {
                _collision.right = true;
                break;
            }

            case game::collision::colDownLeft: {
                if (_position.x <= blockBounds.left + 42 && collidedBlock.blockType != game::blockType::quicksand) {
                    _collision.down = true;
                    _position.y = blockBounds.top - _tileYSize;
                }
                break;
            }

            case game::collision::colDownRight: {
                if (_position.x + _tileXSize >= blockBounds.left + 43 &&
                    collidedBlock.blockType != game::blockType::quicksand) {
                    _collision.down = true;
                    _position.y = blockBounds.top - _tileYSize;
                }
                break;
            }

            default: {
                break;
            }
        }
    }
}

void game::heroView::affectCollision(const uint8_t collisionFrom, const Block &collidedBlock) {
    switch (collidedBlock.blockType) {
        case game::blockType::quicksand : {
            if (collisionFrom == game::collision::colDown ||
                collisionFrom == game::collision::colDownRight ||
                collisionFrom == game::collision::colDownLeft) {
                if (_hp == 0) {
                    decreaseLifes();
                    if (getLifes() == 0) {
                        _gameOver = true;
                    }
                    increaseHp(_hpMax);
                }
                decreaseHp(1);
            }
            break;
        }

        case game::blockType::coin : {
            Block &sb = const_cast<Block &>(collidedBlock);
            if (collisionFrom == game::collision::colDown
                || collisionFrom == game::collision::colUp
                || collisionFrom == game::collision::colRight
                || collisionFrom == game::collision::colLeft) {
                sb.collectCoin();
                increaseCoins();
            }
            break;
        }

        case game::blockType::ladder : {
            if (collisionFrom == game::collision::colDown){
                _collision.down = true;
            }
            break;
        }

        case game::blockType::collapsingFloor :
        case game::blockType::collFloor : {
            Block &sb = const_cast<Block &>(collidedBlock);
            if (collisionFrom == game::collision::colDown || collisionFrom == game::collision::colUp) {
                sb.breakBlock();
            }
            break;
        }

        default: {
            break;
        }
    }

}

bool game::heroView::checkBounds(sf::FloatRect &heroNextRect) {
    if (heroNextRect.top >= _window.getSize().y / 2 + _window.getView().getCenter().y) {
        decreaseHp(_hpMax);
        decreaseLifes();
        decreaseLifes();
        _gameOver = true;
        return false;
    }

    if (heroNextRect.left <= _window.getView().getCenter().x - _window.getView().getSize().x / 2) {
        _position.x = _window.getView().getCenter().x + _window.getView().getSize().x / 2 - _tileXSize;
//        _collision.left = true;
    }

    if (heroNextRect.left + _tileXSize >= _window.getView().getCenter().x + _window.getView().getSize().x / 2) {
        _position.x = _window.getView().getCenter().x - _window.getView().getSize().x / 2;
    }

//    return false;
    return true;
}

void game::heroView::collisionCheck(int time, const game::mapView &map) {
    sf::FloatRect heroNextRect = getNextFrame(time);

    if (checkBounds(heroNextRect)) {

        uint16_t yPos = 0;
        while (heroNextRect.top > map.blocks[yPos][0].blockSprite.getPosition().y) {
            yPos++;
            if (yPos == map.blocks.size()) {
                break;
            }
        }
        yPos != 0 ? yPos-- : yPos;

        uint16_t xPos = 0;
        while (heroNextRect.left > map.blocks[yPos][xPos].blockSprite.getPosition().x) {
            xPos++;
            if (xPos == map.blocks.size()) {
                break;
            }
        }
        xPos != 0? xPos-- : xPos;

        uint16_t yPosLimit =
                yPos + 3 >= map.blocks.size() ?
                static_cast<uint16_t >(map.blocks.size()) :
                static_cast<uint16_t >(yPos + 3);

        uint16_t xPosLimit =
                xPos + 3 >= map.blocks[0].size() ?
                static_cast<uint16_t >(map.blocks[0].size()) :
                static_cast<uint16_t >(xPos + 3);

        uint8_t collisionFrom = 0;

        for (int i = yPos; i < yPosLimit; i++) {
            for (int j = xPos; j < xPosLimit; j++) {
                if (heroNextRect.intersects(map.blocks[i][j].blockSprite.getGlobalBounds()) &&
                    map.blocks[i][j].blockType != game::blockType::empty) {

                    if (map.blocks[i][j].blockType != game::blockType::coin) {
                        resolveCollision(collisionFrom, map.blocks[i][j]);
                    }

                    affectCollision(collisionFrom, map.blocks[i][j]);
                }
                ++collisionFrom;
            }
        }
    }

}

void game::heroView::gravityFall(int time) {
    if (!_collision.down) {
        alterY(_ySpeed * time / _speedFactor);
        _ySpeed += _gravity * time / 85;
    } else {
        if (_ySpeed > 0) {
            _ySpeed = 0;
            _jumpsDone = 0;
        }
    }
}

void game::heroView::setHeroToPoint(const sf::Vector2f point) {
    _position.x = point.x + _tileXSize / 2;
    _position.y = point.y - _tileYSize * 1.5f;
}





