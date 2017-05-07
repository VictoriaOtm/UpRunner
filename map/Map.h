//
// Created by otm on 26.04.17.
//

#ifndef UPRUN_MAP_H
#define UPRUN_MAP_H


#include <vector>
#include <boost/circular_buffer.hpp>

namespace game {
    enum blockType{
        empty,
        staticFloor, //game::blockType::empty
        ladder,
        quicksand,
        collapsingFloor,
        collFloor
    };

    class Map {
    public:
        Map();

        Map(const Map& rhs);

        virtual ~Map() noexcept = default;

        void generate();

    protected:
        boost::circular_buffer<std::vector<uint8_t >> _map;

        std::size_t curLine;
        bool _mapUpdated;

        uint16_t _height;
        uint16_t _width;
    };

}


#endif //UPRUN_MAP_H
