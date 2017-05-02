#include "blockView.h"

game::blockView::blockView() throw(game::error::textureNotFound) {
    if (_blockT.loadFromFile("./textures/blockTS.png")) {
        _block.setTexture(_blockT);
    } else {
        throw game::error::textureNotFound("Texture not found");
    }
}


void game::blockView::draw(sf::RenderWindow &window) {

    window.draw(_block);
}

void game::blockView::update() {
    _block.setPosition(0, 300);
}
