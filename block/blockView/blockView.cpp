#include "blockView.h"

game::blockView::blockView() throw(game::error::textureNotFound) {
    if (_texture.loadFromFile("./textures/blockTS.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

game::blockView::blockView(const std::string &newName) throw(game::error::textureNotFound) : block(newName) {
    if (_texture.loadFromFile("./textures/blockTS.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::blockView::parseTexture() {
    _sprites.resize(8);

    for (int row = 0; row < 8; row++) {
        _sprites[row].resize(13, sf::Sprite(_texture));

        for (int col = 0; col < 13; col++) {
            _sprites[row][col].setTextureRect(sf::IntRect(col * _tileXSize, row * _tileYSize, _tileXSize, _tileYSize));
        }
    }

    _curSprite = &_sprites[game::blockSpritesFacing_row::Block][game::blockSpritesFacing_col::Brown];
}

void game::blockView::draw(sf::RenderWindow &window) {
    switch (type) {
        case Brown_ : {
            _curSprite = &_sprites[game::blockSpritesFacing_row::Block][game::blockSpritesFacing_col::Brown];
            break;
        }

        case Red_ : {
            _curSprite = &_sprites[game::blockSpritesFacing_row::Block][game::blockSpritesFacing_col::Red];
            break;
        }

        case Gray_ : {
            _curSprite = &_sprites[game::blockSpritesFacing_row::Block][game::blockSpritesFacing_col::Gray];
            break;
        }

        default: {

            break;
        }
    }

    _curSprite->setPosition(getX(), getY());
    _curSprite->setScale(sf::Vector2f(0.5f, 0.25f));
    window.draw(*_curSprite);
}

//void game::blockView::changeMovementVec(const int xRotation, const int yRotation) {
//    _movementVector.x += xRotation;
//    _movementVector.y += yRotation;
//}