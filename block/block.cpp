#include "block.h"

namespace game{
    block::block(const std::string &new_name) :
            _name(new_name),
            type(Brown_)
    {}

    block::block() :
            type(Brown_)
    {}

    void block::alterX(double dx) {
        block_position.x += dx;
    }

    void block::alterY(double dy) {
        block_position.y += dy;
    }

    void block::setX(double dx) {
        block_position.x = dx;
    }

    void block::setY(double dy) {
        block_position.y = dy;
    }

    void block::set_type(block_type new_type){
        type = new_type;
    }

    const block_type block::get_type() const{
        return type;
    }

    const double block::getX() const {
        return block_position.x;
    }

    const double block::getY() const {
        return block_position.y;
    }
}