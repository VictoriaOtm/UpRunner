//
// Created by otm on 30.04.17.
//

#include "object.h"

namespace game{

    void object::alterX(double dx) {
        _position.x += dx;
    }

    void object::alterY(double dy) {
        _position.y += dy;
    }

    const double object::getX() const {
        return _position.x;
    }

    const double object::getY() const {
        return _position.y;
    }

    object::object() {

    }

    object::object(const object &rhs) {

    }

}