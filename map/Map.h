//
// Created by otm on 26.04.17.
//

#ifndef UPRUN_MAP_H
#define UPRUN_MAP_H


#include <vector>
#include <boost/circular_buffer.hpp>
#include <random>

namespace game {
    enum blockType {
        empty,
        staticFloor,
        ladder,
        quicksand,
        collapsingFloor,
        collFloor,
        coin,
        startingPosition
    };

    class Map {
    public:
        Map();

        Map(const Map &rhs);

        virtual ~Map() noexcept = default;

        std::size_t getCurrLine();

        void generate();

    protected:
        boost::circular_buffer<std::vector<uint8_t >> _map;

        std::size_t curLine;
        bool _mapUpdated;

        uint16_t _height;
        uint16_t _width;

        bool ladderIsBuilding = false;
        uint8_t ladderPos = 0;

        std::random_device rd;
        std::mt19937 gen;
        std::uniform_int_distribution<> dis0_10;
        std::uniform_int_distribution<> dis1_3;
        std::uniform_int_distribution<> dis2_6;
        std::uniform_int_distribution<> dis4_6;
        std::uniform_int_distribution<> dis0_100;

        uint8_t curLogicBlockSize = 4;
        uint8_t curLogicBlockLine = 2;
    };

}


#endif //UPRUN_MAP_H