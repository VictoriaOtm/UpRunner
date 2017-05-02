//
// Created by otm on 22.04.17.
//

#include "heroView.h"

game::heroView::heroView() throw(game::error::textureNotFound) {
    if (_texture.loadFromFile("./textures/heroTS1.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::heroView::update(int time) {
    //move
    // check collision -> vector of collision -> move if true

    collisionCheck(time);
    alterMovementVec();
    gravityFall(time);

    switch (_movementVector.x) {
        case game::movement::left: {
            alterX(_xSpeed * time * game::movement::left / _speedFactor);
            break;
        }

        case game::movement::right: {
            alterX(_xSpeed * time * game::movement::right / _speedFactor);
            break;
        }

        default: {
            break;
        }
    }

    //перепишется в зависимости от лестниц
//    switch (_movementVector.y) {
//        case game::movement::up: {
//            alterY(_xSpeed * time * game::movement::up / 50);
//            break;
//        }
//
//        case game::movement::down: {
//            alterY(_xSpeed * time * game::movement::down / 50);
//            break;
//        }
//
//        default: {
//            break;
//        }
//    }

    if (_movementVector.x != 0) {
        _curFrame += time / 80.d;
        _curFrame >= 3 ? _curFrame = 0 : _curFrame;
    } else {
        _curFrame = 0;
    }

    _collision.reset();

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

void game::heroView::collisionCheck(int time) {
    sf::FloatRect heroNextRect = _curSprite->getGlobalBounds();
    heroNextRect.top += _ySpeed * time / _speedFactor;

    switch (_movementVector.x){
        case game::movement::left:{
            heroNextRect.left += _xSpeed * time * game::movement::left / _speedFactor;
            break;
        }

        case game::movement::right:{
            heroNextRect.left += _xSpeed * time * game::movement::right / _speedFactor;
            break;
        }

        default:{
            break;
        }
    }

    if (heroNextRect.intersects(sf::FloatRect(0, 300, 400, 300))) {
        _collision.down = true;
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
    }
     else {
        if (_ySpeed > 0){
            _ySpeed = 0;
            _jumpsDone = 0;
        }
    }
}
