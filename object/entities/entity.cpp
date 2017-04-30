//
// Created by otm on 22.04.17.
//

#include "entity.h"

namespace game {
    entity::entity(const std::string &new_name) :
            _name(new_name),
            _hp(100),
            _xSpeed(12),
            _ySpeed(0),
            _jumpsDone(0)  {}

//    entity::entity(const entity &rhs) :
//            _name(rhs._name),
//            _hp(rhs._hp),
//            _xSpeed(rhs._xSpeed),
//            _position(rhs._position.x, rhs._position.y) {}

    const double entity::getSpeed() const {
        return _xSpeed;
    }

    entity::entity() : _hp(100),
                       _xSpeed(12),
                       _ySpeed(0),
                       _jumpsDone(0){}

    void entity::jump() {
//        нельзя прыгнуть больше 2 раз.
        if (_jumpsDone <= 1){
            _ySpeed = -_ySpeedMax;
            ++_jumpsDone;
        }
    }
}
