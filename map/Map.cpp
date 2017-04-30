//
// Created by otm on 26.04.17.
//

#include "Map.h"

game::Map::Map(): _map(32), curLine(1), _height(16), _width(12){
    //_map.push_back(std::vector(_width, game::blockType::staticFloor));
}

game::Map::Map(const game::Map &rhs) {

}

void game::Map::generate() {

}
