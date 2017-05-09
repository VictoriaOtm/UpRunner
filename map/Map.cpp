//
// Created by otm on 26.04.17.
//

#include "Map.h"
#include "stdlib.h"
#include <ctime>
#include <iostream>

game::Map::Map() : _map(30), curLine(1), _height(16), _width(12), _mapUpdated(false), gen(rd()), dis0_10(0, 10),
                   dis1_3(1, 3), dis2_6(2, 6) {
    _map.resize(18);
    _map[_map.size()-1].resize(_width, game::blockType::staticFloor);

    for (size_t i = 0; i < _map.size()-1; i++) {
        generate();
    }
    _mapUpdated = false;
}

game::Map::Map(const game::Map &rhs) {

}

void game::Map::generate() {
    _mapUpdated = true;
    _map.pop_front();


    std::vector<uint8_t> new_vector;

    switch (curLine % 5) {
        case 0: {
            new_vector.resize(_width, game::blockType::staticFloor);

            for (int i = 0; i < dis1_3(gen); i++) {
                int space = dis0_10(gen);
                int amount = dis2_6(gen);
                for (int j = space; j < space + amount; j++)
                    new_vector[j] = game::blockType::empty;
            }
            break;
        }
        case 1: {


            break;
        }
        case 2: {
            new_vector.resize(_width, game::blockType::empty);
            for (int i = 0; i < dis1_3(gen); i++) {
                int space = dis0_10(gen);
                int amount = dis1_3(gen);
                for (int j = space; j < space + amount; j++) {
                    if (dis0_10(gen) == 0) {
                        new_vector[j] = game::blockType::quicksand;
                    } else{
                        new_vector[j] = game::blockType::collapsingFloor;
                    }
                }
            }
            break;
        }
        case 3: {
            break;
        }
        case 4:{
            new_vector.resize(_width, game::blockType::empty);
            for (int i = 0; i < dis1_3(gen); i++) {
                int space = dis0_10(gen);
                int amount = dis1_3(gen);
                for (int j = space; j < space + amount; j++)
                    new_vector[j] = game::blockType::staticFloor;
            }
            break;
        }

        case 5:{
            break;
        }

        default: {
            break;
        }
    }
    if (new_vector.empty()) {
        new_vector.resize(_width, game::blockType::empty);
    }
    _map.push_back(new_vector);
    curLine++;
}
