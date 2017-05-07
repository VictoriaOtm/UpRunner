#include "blockView.h"

game::blockView::blockView() throw(game::error::textureNotFound) {
    if (_blockT.loadFromFile("./textures/blocksTS.png")) {
        parseTexture();
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}

void game::blockView::update() {
    //_block.setPosition(0, 300);
}


void game::blockView::parseTexture() {
    _sprites.resize(1);

    _sprites[0].resize(8, sf::Sprite(_blockT));

    for (int col = 0; col < 8; col++) {
        _sprites[0][col].setTextureRect(sf::IntRect(col * _tileXSize, 0, _tileXSize, _tileYSize));
    }

    _curSprite = &_sprites[0][game::blockType::empty];
}

void game::blockView::draw(sf::RenderWindow &window, char type, int row, int col) {
    switch (type) {
        case '0' : {
            _curSprite = &_sprites[0][game::blockType::empty];
            break;
        }

        case '1' : {
            _curSprite = &_sprites[0][game::blockType::staticFloor];
            break;
        }
        case '2' : {
            _curSprite = &_sprites[0][game::blockType::ladder];
            break;
        }

        case '3': {
            _curSprite = &_sprites[0][game::blockType::quicksand];
            break;
        }

        case '4': {
            _curSprite = &_sprites[0][game::blockType::collapsingFloor];
            break;
        }

        case '5': {
            _curSprite = &_sprites[0][game::blockType::collFloor];
            break;
        }

        default: {

            break;
        }
    }

    _curSprite->setPosition(col * 64, 960 - (row + 1) * 64);
    _curSprite->setScale(sf::Vector2f(0.5f, 0.5f));
    window.draw(*_curSprite);
}
