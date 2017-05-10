//
// Created by otm on 22.04.17.
//

#include <math.h>
#include "heroView.h"

game::heroView::heroView() throw(game::error::textureNotFound): _gameOver(false), _isFalling(true), _isLadder(false) {
    if (_texture.loadFromFile("./textures/heroTS1.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::heroView::update(int time, const boost::circular_buffer<std::vector<Block>> &_block) {
    _curSprite->move(0, _speedOnMap);

    collisionCheck(time, _block);
    //alterMovementVec();
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

void game::heroView::draw(sf::RenderWindow &window) {
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
    window.draw(*_curSprite);
}

void game::heroView::parseTexture() {
    _sprites.resize(3);

    for (int row = 0; row < 3; row++) {
        _sprites[row].resize(3, sf::Sprite(_texture));

        for (int col = 0; col < 3; col++) {
            _sprites[row][col].setTextureRect(sf::IntRect(col * _tileXSize, row * _tileYSize, _tileXSize, _tileYSize));
        }
    }

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
    }

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
                sb.collect();
                increaseCoins();
            }
            break;
        }

        case game::blockType::collapsingFloor :
        case game::blockType::collFloor : {
            Block &sb = const_cast<Block &>(collidedBlock);
            if (collisionFrom == game::collision::colDown || collisionFrom == game::collision::colUp) {
                sb.breakBlock();
                jump();
            }
            break;
        }

        default: {
            break;
        }
    }

}

void game::heroView::collisionCheck(int time, const boost::circular_buffer<std::vector<Block>> &_blocks) {
    sf::FloatRect heroNextRect = getNextFrame(time);

    uint16_t xPos = static_cast<uint16_t >(heroNextRect.left / 64);
    uint16_t yPos = static_cast<uint16_t >(heroNextRect.top / 64 + 3);

    if (heroNextRect.top >= 960) {
        decreaseHp(_hpMax);
        decreaseLifes();
        decreaseLifes();
        _gameOver = true;
    } else {
        uint8_t collisionFrom = 0;

        for (int i = yPos; i < (yPos + 3 >= 18 ? 18 : yPos + 3); i++) {
            for (int j = xPos; j < (xPos + 3 >= 13 ? 13 : xPos + 3); j++) {
                if (heroNextRect.intersects(_blocks[i][j].blockSprite.getGlobalBounds()) &&
                    _blocks[i][j].blockType != game::blockType::empty) {
                    resolveCollision(collisionFrom, _blocks[i][j]);
                    affectCollision(collisionFrom, _blocks[i][j]);
                }
                ++collisionFrom;
            }
        }
    }
}

void game::heroView::alterMovementVec() {
    if ((_movementVector.x == game::movement::right && _collision.right) ||
        (_movementVector.x == game::movement::left && _collision.left)) {

        _movementVector.x = 0;
    }

    if ((_movementVector.y == game::movement::up && _collision.up) ||
        (_movementVector.y == game::movement::down && _collision.down)) {

        _movementVector.y = 0;
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





