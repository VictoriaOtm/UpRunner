//
// Created by otm on 22.04.17.
//
#include <iostream>

#ifndef UPRUN_ENTITY_H
#define UPRUN_ENTITY_H

namespace game {

    class entity {
    public:
        entity();

        entity(const std::string &new_name);

        //virtual entity(const entity &rhs);

        virtual ~entity() noexcept = default;

        void alterX(double dx);

        void alterY(double dy);

        const double getX() const;

        const double getY() const;

        const double getSpeed() const;

    protected:
        const std::string _name;
        uint16_t _hp;

        double _speed;

        struct position {
            position() : x(0), y(0) {}

            position(double newX, double newY) : x(newX), y(newY) {}

            double x;
            double y;
        } _position;

    };
}

#endif //UPRUN_ENTITY_H
