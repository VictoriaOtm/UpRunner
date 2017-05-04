//
// Created by otm on 26.04.17.
//

#include "Map.h"
#include "stdlib.h"
#include <ctime>

game::Map::Map(): _map(32), curLine(1), _height(16), _width(12){
    std::vector<char> vect {'1','1','1','1','1','1','1','1','1','1','1','1'} ;
    std::vector<char> vect1 {'1','1','1','1','1','0','0','0','1','1','1','1'} ;
    _map.push_back(vect);
    _map.push_back(vect1);
    for(int i = 0; i < 30; ++i){
        generate();
    }

}

game::Map::Map(const game::Map &rhs) {

}

void game::Map::generate() {
    //std::vector<char> *d_vector = _map.back();      /// последняя строка карты
    //std::vector<char> d1_vector = *(d_vector);
    std::vector<char> new_vector;           //вектор, который мы будем добавлять в конец массива. 1 вызов метода - 1 новая строка.

    new_vector.assign(12, '1');

    int count = (rand()%10);  // число пустот в ряду

    if (6 <= count && count <= 9 ){
        count = 5;
    }
    if (0 <= count && count <= 4 ){
        count = 2;
    }

    int control = 0;
    int random = (rand()%2);
    int sum, del;
    switch(random) {
        case 0: {
            do {
                ++control;
            } while (_map[_map.size()-1][control] != '0');
            control = control - 1;
            sum = control + count;
            if (sum >=12){
                sum = 12;
            }
            for (int j = control; j < sum; j++) {
                new_vector[j] = '0';
            }
            break;
        }

        case 1: {
            control = 11;
            do {
                control--;
            } while (_map[_map.size()-1][control] != '0');

            del = control - count;
            if (del < 0){
                del = 0;
            }
            for (int j = control; j > del; j--) {
                new_vector[j] = '0';
            }
            break;
        }
        default: {
            break;
        }
    }
    _map.push_back(new_vector);

}

const boost::circular_buffer<std::vector<char>> game::Map::getBuffer() const {
    return _map;
}
