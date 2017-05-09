//
// Created by otm on 22.04.17.
//

#include "entity.h"

namespace game {
//    entity::entity(const entity &rhs) :
//            _name(rhs._name),
//            _hp(rhs._hp),
//            _xSpeed(rhs._xSpeed),
//            _position(rhs._position.x, rhs._position.y) {}

    const double entity::getSpeed() const {
        return _xSpeed;
    }

    entity::entity() : _hp(250),
                       _xSpeed(20),
                       _ySpeed(0),
                       _jumpsDone(0){}

    void entity::jump() {
//        нельзя прыгнуть больше 2 раз.
        if (_jumpsDone <= 1){
            _ySpeed = -_ySpeedMax;
            ++_jumpsDone;
        }
    }

    void entity::increaseHp(const uint16_t dHp) {
        if (_hp + dHp <= _hpMax){
            _hp += dHp;
        }
        else{
            _hp = _hpMax;
        }
    }

    void entity::decreaseHp(const uint16_t dHp) {
        if (_hp - dHp >= 0){
            _hp -= dHp;
        }
        else{
            _hp = 0;
        }
    }

    const uint16_t entity::getHp() const {
        return _hp;
    }
}
