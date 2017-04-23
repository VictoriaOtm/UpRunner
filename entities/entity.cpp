//
// Created by otm on 22.04.17.
//

#include "entity.h"

namespace game {
    entity::entity(const std::string &new_name) :
            _name(new_name),
            _hp(100),
            _speed(12) {}

//    entity::entity(const entity &rhs) :
//            _name(rhs._name),
//            _hp(rhs._hp),
//            _speed(rhs._speed),
//            _position(rhs._position.x, rhs._position.y) {}

    void entity::alterX(double dx) {
        _position.x += dx;
    }

    void entity::alterY(double dy) {
        _position.y += dy;
    }

    const double entity::getSpeed() const {
        return _speed;
    }

    const double entity::getX() const {
        return _position.x;
    }

    const double entity::getY() const {
        return _position.y;
    }

    entity::entity() : _hp(100),
                       _speed(12) {}
}



