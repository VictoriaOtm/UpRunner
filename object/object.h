//
// Created by otm on 30.04.17.
//

#ifndef UPRUN_OBJECT_H
#define UPRUN_OBJECT_H

#include <iostream>

namespace game{
    class object {
    public:
        object();

        object(const object &rhs);

        virtual ~object() noexcept = default;

        void alterX(double dx);

        void alterY(double dy);

        const double getX() const;

        const double getY() const;

    protected:

        struct position {
            position() : x(600), y(200) {}

            position(double newX, double newY) : x(newX), y(newY) {}

            double x;
            double y;
        } _position;
    };
}

#endif //UPRUN_OBJECT_H
