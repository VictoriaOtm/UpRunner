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
        collFloor1
    };

    class Map {
    public:
        Map();

        Map(const Map& rhs);

        ~Map() noexcept = default;

        void generate();

        const boost::circular_buffer<std::vector<char>> getBuffer() const;

    private:
        boost::circular_buffer<std::vector<char>> _map;

        std::size_t curLine;

        uint16_t _height;
        uint16_t _width;
    };

}


#endif //UPRUN_MAP_H
