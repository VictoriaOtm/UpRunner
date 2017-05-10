//
// Created by root on 07.05.17.
//

#include "mapView.h"

game::mapView::mapView(sf::RenderWindow &window) : _window(window), blocks(18) {
    if (_blocksTexture.loadFromFile("./textures/blocksTS.png")) {
        blocks.resize(_map.size());
        long currRow = 0;

        float scaleFactorH = (static_cast<float>(_window.getSize().y) / 960.f) * 0.5f;
        float scaleFactorW = (static_cast<float>(_window.getSize().x) / 768.f) * 0.5f;

        for (long i = _map.size() - 1; i >= 0; i--) {
            blocks[currRow].resize(_width);
            for (long j = 0; j < _width; j++) {
                blocks[currRow][j].blockType = _map[i][j];
                blocks[currRow][j].blockSprite.setTexture(_blocksTexture);
                blocks[currRow][j].blockSprite.setTextureRect(
                        sf::IntRect(blocks[currRow][j].blockType * _tileWidth, 0, _tileWidth, _tileHeight));
                blocks[currRow][j].blockSprite.setScale(scaleFactorW, scaleFactorH);
                blocks[currRow][j].blockSprite.setPosition(j * _tileHeight * scaleFactorW,
                                                           (currRow) * _tileHeight * scaleFactorH);
            }
            currRow++;
        }

        _tileHeight *= scaleFactorH;
        _tileWidth *= scaleFactorW;
    }
}

game::mapView::mapView(const game::mapView &rhs) : Map(rhs), _window(rhs._window) {}

void game::mapView::update() {
    for (auto &i : blocks) {
        for (auto &j : i) {
            j.blockSprite.move(0, _speed);
        }
    }
    if (blocks[blocks.size() - 1][0].blockSprite.getPosition().y > _map.size() * _tileHeight) {
        generate();

        float scaleFactorH = (static_cast<float>(_window.getSize().y) / 960.f) * 0.5f;
        float scaleFactorW = (static_cast<float>(_window.getSize().x) / 768.f) * 0.5f;

        blocks.pop_back();
        blocks.push_front(std::vector<Block>(_width));

        for (int i = 0; i < _width; i++) {
            blocks[0][i].blockType = _map[_map.size() - 1][i];
            blocks[0][i].blockSprite.setTexture(_blocksTexture);
            blocks[0][i].blockSprite.setTextureRect(
                    sf::IntRect(blocks[0][i].blockType * 128, 0, 128, 128));
            blocks[0][i].blockSprite.setScale(sf::Vector2f(scaleFactorW, scaleFactorH));
            blocks[0][i].blockSprite.setPosition(blocks[1][i].blockSprite.getPosition() - sf::Vector2f(0, _tileHeight));
        }
    }
}

void game::mapView::draw() {
    for (auto it = blocks.begin(); it < blocks.end(); it++) {
        for (auto j : *it) {
            _window.draw(j.blockSprite);
        }
    }
}

const float game::mapView::tileHeight() const {
    return _tileHeight;
}

const float game::mapView::tileWidth() const {
    return _tileWidth;
}

sf::Vector2f game::mapView::startingPoint() {
    return blocks[blocks.size() - 2][1].blockSprite.getPosition();
}
