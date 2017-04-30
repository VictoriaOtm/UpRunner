//
// Created by otm on 22.04.17.
//
#include <iostream>
#include "../object.h"

#ifndef UPRUN_ENTITY_H
#define UPRUN_ENTITY_H

namespace game {

    class entity : public object{
    public:
        entity();

        entity(const std::string &new_name);

        //virtual entity(const entity &rhs);

        virtual ~entity() noexcept = default;

        void jump();

        const double getSpeed() const;

    protected:
        const std::string _name;
        uint16_t _hp;

        uint8_t _jumpsDone;

        double _xSpeed;
        double _ySpeed;

        const double _ySpeedMax = 30;

        const double _gravity = 10;

        struct collision {
            collision() : up(false), down(false),
                          left(false), right(false){}

            void reset(){
                up = down = left = right = false;
            }

            bool up;
            bool down;
            bool left;
            bool right;
        }_collision;

    };
}

#endif //UPRUN_ENTITY_H
