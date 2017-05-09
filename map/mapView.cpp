//
// Created by root on 07.05.17.
//

#include "mapView.h"

game::mapView::mapView(sf::RenderWindow &window) : _window(window), blocks(18) {
    if (_blocksTexture.loadFromFile("./textures/blocksTS.png")) {
        blocks.resize(_map.size());
        long currRow = 0;

        for (long i = _map.size() - 1; i >= 0; i--) {
            blocks[currRow].resize(_width);
            for (long j = 0; j < _width; j++) {
                blocks[currRow][j].blockType = _map[i][j];
                blocks[currRow][j].blockSprite.setTexture(_blocksTexture);
                blocks[currRow][j].blockSprite.setTextureRect(sf::IntRect(blocks[currRow][j].blockType * 128, 0, 128, 128));
                blocks[currRow][j].blockSprite.setScale(sf::Vector2f(0.5f, 0.5f));
                blocks[currRow][j].blockSprite.setPosition(j * 64, (currRow - 3) * 64);
            }
            currRow++;
        }
    }
}

game::mapView::mapView(const game::mapView &rhs) : Map(rhs), _window(rhs._window) {}

void game::mapView::update() {
    for (auto &i : blocks){
        for (auto &j : i){
            j.blockSprite.move(0, _speed);
        }
    }
    if (blocks[blocks.size() - 1][0].blockSprite.getPosition().y > 960){
        generate();
        blocks.pop_back();
        blocks.push_front(std::vector<Block>(_width));
        for (int i = 0; i < _width; i++){
            blocks[0][i].blockType = _map[_map.size() - 1][i];
            blocks[0][i].blockSprite.setTexture(_blocksTexture);
            blocks[0][i].blockSprite.setTextureRect(sf::IntRect(blocks[0][i].blockType * 128, 0, 128, 128));
            blocks[0][i].blockSprite.setScale(sf::Vector2f(0.5f, 0.5f));
            blocks[0][i].blockSprite.setPosition(i * 64, (0) * 64);
        }
    }
}

void game::mapView::draw() {
    for (auto it = blocks.begin() + 3; it < blocks.end(); it++) {
        for (auto j : *it) {
            _window.draw(j.blockSprite);
        }
    }
}

const uint16_t game::mapView::tileHeight() const {
    return _tileHeight;
}

const uint16_t game::mapView::tileWidth() const {
    return _tileWidth;
}
