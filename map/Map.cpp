//
// Created by otm on 26.04.17.
//

#include "Map.h"
#include "stdlib.h"
#include <ctime>
#include <iostream>

game::Map::Map() : _map(32), curLine(1), _height(16), _width(12) {
    std::vector<char> vect{'2', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '2'};
    _map.push_back(vect);
    _map.push_back(vect);

    for (int i = 0; i < 30; ++i) {
        generate();
    }
}

game::Map::Map(const game::Map &rhs) {

}

void game::Map::generate() {
    // 0 - пустота
    // 1 - обычный блок
    // 2 - лестница
    // 3 - пески
    // 4 - разрушающийся блок
    std::vector<char> new_vector;
    srand(time(0));
    if (_map[_map.size() - 1][0] == '2') {
        if (_map[_map.size() - 1][1] == '1') {
            new_vector.assign(12, '0');
            new_vector[0] = '2';
            int destroy = (rand() % 12);
            if (destroy == 0) {
                destroy++;
            }
            new_vector[destroy] = '4';
            int sand = (rand() % 12);
            if (sand == 0 || sand == destroy) {
                sand++;
            }
            new_vector[sand] = '3';

            _map.push_back(new_vector);
        }
        if (_map[_map.size() - 1][1] == '0') {
            if (_map[_map.size() - 2][1] == '0' && _map[_map.size() - 2][1] == '0' && _map[_map.size() - 3][1] == '0') {
                new_vector.assign(12, '1');

                new_vector[0] = '2';
                int destroy = (rand() % 12);
                if (destroy == 0) {
                    destroy++;
                }
                new_vector[destroy] = '4';
                int sand = (rand() % 12);
                if (sand == 0 || sand == destroy) {
                    sand++;
                }
                new_vector[sand] = '3';
                _map.push_back(new_vector);
            } else {
                new_vector.assign(12, '0');

                new_vector[0] = '2';
                int destroy = (rand() % 12);
                if (destroy == 0) {
                    destroy++;
                }
                new_vector[destroy] = '4';
                _map.push_back(new_vector);
            }
        }
    }
}

const boost::circular_buffer<std::vector<char>> game::Map::getBuffer() const {
    return _map;
}