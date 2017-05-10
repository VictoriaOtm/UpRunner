//
// Created by otm on 26.04.17.
//

#include "Map.h"
#include "stdlib.h"
#include <ctime>
#include <iostream>

game::Map::Map() : _map(), curLine(2), _height(16), _width(12), _mapUpdated(false), gen(rd()), dis0_10(0, 10),
                   dis1_3(1, 3), dis2_6(2, 6), dis4_6(4, 6), dis0_100(0, 100) {
    _map.resize(18);
    _map[_map.size() - 1].resize(_width, game::blockType::staticFloor);
    _map[_map.size() - 2].resize(_width, game::blockType::staticFloor);


    for (size_t i = 0; i < _map.size() - 2; i++) {
        generate();
    }
    _mapUpdated = false;
}

game::Map::Map(const game::Map &rhs) {

}

void game::Map::generate() {





    _mapUpdated = true;
    _map.pop_front();


    std::vector<uint8_t> newLine;

    switch (curLogicBlockLine % curLogicBlockSize) {
        case 0: {
            curLogicBlockSize = static_cast<uint8_t >(dis4_6(gen));
            curLogicBlockLine = 0;
            newLine.resize(_width, game::blockType::staticFloor);

            uint8_t spacesAmount = static_cast<uint8_t >(dis1_3(gen));
            uint8_t curSpacePos = 0;

            for (uint8_t space = 0; space < spacesAmount; space++) {
                uint8_t curSpaceSize = static_cast<uint8_t >(dis4_6(gen) - 2);
                curSpacePos += static_cast<uint8_t >(dis2_6(gen));

                if (curSpacePos + curSpaceSize < _width - 1) {
                    for (uint8_t i = curSpacePos; i < curSpacePos + curSpaceSize; i++) {
                        newLine[i] = game::blockType::empty;
                    }
                }
            }

            if (dis0_100(gen) < 15) {
                uint8_t trapPos = static_cast<uint8_t >(dis0_10(gen) + dis0_100(gen) % 2);
                uint8_t trapSize = static_cast<uint8_t >(dis1_3(gen));

                while (trapPos + trapSize < _width &&
                       (newLine[trapPos] == game::blockType::empty ||
                        newLine[trapPos + trapSize] == game::blockType::empty)) {
                    trapPos++;
                }

                for (uint8_t i = trapPos; i < (trapPos + trapSize) && i < _width; i++) {
                    newLine[i] = game::blockType::quicksand;
                }

            }

            if (ladderIsBuilding) {
                newLine[ladderPos] = game::blockType::ladder;
                if (ladderPos - 1 >= 0) {
                    if (newLine[ladderPos - 1] != game::blockType::empty) {
                        ladderIsBuilding = false;
                        break;
                    }
                }

                if (ladderPos + 1 < _width) {
                    if (newLine[ladderPos + 1] != game::blockType::empty) {
                        ladderIsBuilding = false;
                        break;
                    }
                }

                ladderPos + 1 < _width ? newLine[ladderPos + 1] = game::blockType::staticFloor : newLine[ladderPos -
                                                                                                         1] = game::blockType::staticFloor;
                ladderIsBuilding = false;
            }

        }
        case 1: {
            if (dis0_100(gen) < 25) {
                newLine.resize(_width, game::blockType::empty);
                uint8_t coinsAmount = static_cast<uint8_t >(dis0_10(gen));
                uint8_t coinsSet = 0;
                switch (coinsAmount % 5) {
                    case 0: {
                        for (uint8_t i = 0; i < _width && coinsSet <= coinsAmount; i += 2, coinsSet++) {
                            newLine[i] = game::blockType::coin;
                        }
                        break;
                    }
                    case 1: {
                        uint8_t coinPos = static_cast<uint8_t>(dis0_10(gen));
                        for (uint8_t i = coinPos; i < _width && i < coinsAmount; i++) {
                            newLine[i] = game::blockType::coin;
                        }
                        break;
                    }

                    case 2: {
                        coinsAmount = static_cast<uint8_t >(coinsAmount / 2 + 1);

                        for (int j = 0; j < 2; j++) {
                            uint8_t coinPos = static_cast<uint8_t>(dis0_10(gen));
                            for (uint8_t i = coinPos; i < _width && i < coinsAmount; i++) {
                                newLine[i] = game::blockType::coin;
                            }
                        }
                        break;
                    }

                    case 3: {
                        coinsAmount = static_cast<uint8_t >(coinsAmount / 3 + 1);

                        for (int j = 0; j < 3; j++) {
                            uint8_t coinPos = static_cast<uint8_t>(dis0_10(gen));
                            for (uint8_t i = coinPos; i < _width && i < coinsAmount; i++) {
                                newLine[i] = game::blockType::coin;
                            }
                        }
                        break;
                    }

                    case 4: {
                        coinsAmount = static_cast<uint8_t >(coinsAmount / 4 + 1);

                        for (int j = 0; j < 4; j++) {
                            uint8_t coinPos = static_cast<uint8_t>(dis0_10(gen));
                            for (uint8_t i = coinPos; i < _width && i < coinsAmount; i++) {
                                newLine[i] = game::blockType::coin;
                            }
                        }
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }
            break;
        }
        case 2: {
            newLine.resize(_width, game::blockType::empty);

            for (uint8_t i = 0; i < _width; i++) {
                if (_map[_map.size() - 2][i] == game::blockType::empty) {
                    uint8_t stepSize = static_cast<uint8_t >(dis1_3(gen) + 1);
                    uint8_t blockType = game::blockType::staticFloor;

                    if (dis0_10(gen) * dis0_10(gen) < 65) {
                        blockType = game::blockType::collapsingFloor;
                    }

                    for (uint8_t j = i + static_cast<uint8_t >(dis0_10(gen) / 5); j < stepSize + i; j++) {
                        newLine[j] = blockType;
                    }
                    break;
                }
            }

            if (dis0_10(gen) * dis2_6(gen) > 50) {
                ladderIsBuilding = true;
                ladderPos = static_cast<uint8_t >(dis0_10(gen) + dis0_10(gen) / 5);
                newLine[ladderPos] = game::blockType::ladder;
            }
        }
        case 3: {
            newLine.resize(_width,game::blockType::empty);
            if (ladderIsBuilding) {
                newLine[ladderPos] = game::blockType::ladder;
            }
            break;
        }
        case 4: {
            newLine.resize(_width,game::blockType::empty);
            if (ladderIsBuilding) {
                newLine[ladderPos] = game::blockType::ladder;
            }
            break;
        }

        case 5: {
            newLine.resize(_width,game::blockType::empty);
            if (ladderIsBuilding) {
                newLine[ladderPos] = game::blockType::ladder;
            }
            break;
        }

        default: {
            break;
        }
    }
    if (newLine.empty()) {
        newLine.resize(_width, game::blockType::empty);
    }

    //Coins!!
    if (dis0_100(gen) < 25) {
        uint8_t coinPos = dis0_10(gen) + 1;
        if (newLine[coinPos] == game::blockType::empty) {
            newLine[coinPos] = game::blockType::coin;
        }
    }


    _map.push_back(newLine);
    curLine++;
    curLogicBlockLine++;
}