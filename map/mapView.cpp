//
// Created by root on 07.05.17.
//

#include "mapView.h"

game::mapView::mapView(sf::RenderWindow &window) : _window(window), blocks(18) {
    if (_blocksTexture.loadFromFile("./textures/blocksTS.png") && _coinTexture.loadFromFile("./textures/coin.png")) {
        blocks.resize(_map.size());
        long currRow = 0;

        for (long i = _map.size() - 1; i >= 0; i--) {
            blocks[currRow].resize(_width);
            for (long j = 0; j < _width; j++) {
                if (_map[i][j] != game::blockType::coin) {
                    blocks[currRow][j].blockType = _map[i][j];
                    blocks[currRow][j].blockSprite.setTexture(_blocksTexture);
                    blocks[currRow][j].blockSprite.setTextureRect(
                            sf::IntRect(blocks[currRow][j].blockType * 128, 0, 128, 128));
                    blocks[currRow][j].blockSprite.setScale(sf::Vector2f(0.5f, 0.5f));
                    blocks[currRow][j].blockSprite.setPosition(j * 64, (currRow) * 64);
                } else {
                    //std::cout << 1;
                    blocks[currRow][j].blockType = _map[i][j];
                    blocks[currRow][j].blockSprite.setTexture(_coinTexture);
                    blocks[currRow][j].blockSprite.setTextureRect(
                            sf::IntRect(0, 0, 32, 32));
                    blocks[currRow][j].blockSprite.setScale(sf::Vector2f(2, 2));
                    blocks[currRow][j].blockSprite.setPosition(j * 64, (currRow) * 64);
                }
            }
            currRow++;
        }
    }
}

game::mapView::mapView(const game::mapView &rhs) : Map(rhs), _window(rhs._window) {}

void game::mapView::update() {
    for (auto &i : blocks) {
        for (auto &j : i) {
            j.blockSprite.move(0, _speed);
        }
    }
    if (blocks[blocks.size() - 1][0].blockSprite.getPosition().y >
        _window.getView().getCenter().y + _window.getView().getSize().y / 2) {
        generate();
        blocks.pop_back();
        blocks.push_front(std::vector<Block>(_width));
        for (int i = 0; i < _width; i++) {
            if (_map[_map.size() - 1][i] != game::blockType::coin) {
                blocks[0][i].blockType = _map[_map.size() - 1][i];
                blocks[0][i].blockSprite.setTexture(_blocksTexture);
                blocks[0][i].blockSprite.setTextureRect(
                        sf::IntRect(blocks[0][i].blockType * 128, 0, 128, 128));
                blocks[0][i].blockSprite.setScale(sf::Vector2f(0.5f, 0.5f));
                blocks[0][i].blockSprite.setPosition(i * 64, blocks[1][i].blockSprite.getPosition().y - 64);
            } else {
                //std::cout << 1;
                blocks[0][i].blockType = _map[_map.size()-1][i];
                blocks[0][i].blockSprite.setTexture(_coinTexture);
                blocks[0][i].blockSprite.setTextureRect(
                        sf::IntRect(0, 0, 32, 32));
                blocks[0][i].blockSprite.setScale(sf::Vector2f(2, 2));
                blocks[0][i].blockSprite.setPosition(i * 64, blocks[1][i].blockSprite.getPosition().y - 64);
            }
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

const uint16_t game::mapView::tileHeight() const {
    return _tileHeight;
}

const uint16_t game::mapView::tileWidth() const {
    return _tileWidth;
}