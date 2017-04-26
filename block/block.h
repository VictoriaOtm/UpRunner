#ifndef UPRUN_BLOCK_H
#define UPRUN_BLOCK_H

#include "../entities/entity.h"
#include <string>

namespace game {

    enum block_type{
        Brown_, Red_, Gray_
    };

    class block {
    public:
        block();

        block(const std::string &new_name);

        virtual ~block() noexcept = default;

        void alterX(double dx);

        void alterY(double dy);

        void setX(double dx);

        void setY(double dy);

        void set_type(block_type);

        const block_type get_type() const;

        const double getX() const;

        const double getY() const;

    protected:
        const std::string _name;

        struct position {
            position() : x(0), y(0) {}

            position(double newX, double newY) : x(newX), y(newY) {}

            double x;
            double y;
        } block_position;

        std::uint16_t _hp; //collapsing blocks

        double speed;   //moving blocks

        block_type type;

    };
}


#endif //UPRUN_BLOCK_H