//
// Created by otm on 26.04.17.
//

#include "Map.h"
#include "stdlib.h"
#include <ctime>
#include <iostream>

game::Map::Map() : _map(18), curLine(1), _height(16), _width(12), _mapUpdated(false) {
    _map.resize(18);
    _map[17].resize(_width, game::blockType::staticFloor);
    _map[16].resize(_width, game::blockType::staticFloor);
    _map[15].resize(_width, game::blockType::empty);
    _map[14].resize(_width, game::blockType::empty);
    _map[13].resize(_width, game::blockType::staticFloor);
    _map[13][3] = _map[13][4] = game::blockType::empty;

    _map[17][0] = _map[16][0] = game::blockType::ladder;

    for (size_t i = 0; i < 13; i++) {
        generate();
    }
    _mapUpdated = false;
}

game::Map::Map(const game::Map &rhs) {

}

void game::Map::generate() {
    _mapUpdated = true;
    _map.pop_front();

    std::vector<uint8_t> new_vector(12, game::blockType::empty);
    srand(time(0));

    if (_map[_map.size() - 1][0] == game::blockType::ladder) {
        if (_map[_map.size() - 1][1] == game::blockType::staticFloor) {
            new_vector[_width - 1] = game::blockType::empty;
            new_vector[0] = game::blockType::empty;

            int destroy = (rand() % 11) + 1;
            new_vector[destroy] = game::blockType::collapsingFloor;

            int sand = (rand() % 11) + 1;
            new_vector[sand] = game::blockType::quicksand;

            _map.push_back(new_vector);
        } else if (_map[_map.size() - 1][1] == game::blockType::empty) {
            if (_map[_map.size() - 2][1] == game::blockType::empty &&
                _map[_map.size() - 2][1] == game::blockType::empty &&
                _map[_map.size() - 3][1] == game::blockType::empty) {

                new_vector[_width - 1] = game::blockType::staticFloor;

                new_vector[0] = game::blockType::ladder;

                int destroy = (rand() % 11) + 1;
                new_vector[destroy] = game::blockType::collapsingFloor;

                int sand = (rand() % 11);
                new_vector[sand] = game::blockType::quicksand;

                _map.push_back(new_vector);
            } else {
                new_vector[0] = game::blockType::ladder;

                int destroy = (rand() % 11) + 1;
                new_vector[destroy] = game::blockType::collapsingFloor;

                _map.push_back(new_vector);
            }
        } else {
            _map.push_back(std::vector<uint8_t>(_width, game::blockType::empty));
        }

    } else {
        _map.push_back(std::vector<uint8_t>(_width, game::blockType::empty));
    }
}

