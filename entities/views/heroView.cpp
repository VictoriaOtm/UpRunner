//
// Created by otm on 22.04.17.
//

#include "heroView.h"

game::heroView::heroView() throw(game::error::textureNotFound) {
    if (_texture.loadFromFile("./textures/heroTS.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::heroView::update(int time) {
    switch (_movementVector.x) {
        case game::movement::left: {
            alterX(_speed * time * game::movement::left / 50);
            break;
        }

        case game::movement::right: {
            alterX(_speed * time * game::movement::right / 50);
            break;
        }

        default: {
            break;
        }
    }

    switch (_movementVector.y) {
        case game::movement::up: {
            alterY(_speed * time * game::movement::up / 50);
            break;
        }

        case game::movement::down: {
            alterY(_speed * time * game::movement::down / 50);
            break;
        }

        default: {
            break;
        }
    }

    if (_movementVector.y != 0 || _movementVector.x != 0) {
        _curFrame += time / 80.d;
        _curFrame >= 3 ? _curFrame = 0 : _curFrame;
    } else {
        _curFrame = 0;
    }

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

game::heroView::heroView(const std::string &newName) throw(game::error::textureNotFound) : hero(newName) {
    if (_texture.loadFromFile("./textures/heroTS.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::heroView::parseTexture() {
    _sprites.resize(4);

    for (int row = 0; row < 4; row++) {
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
