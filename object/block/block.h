#ifndef UPRUN_BLOCK_H
#define UPRUN_BLOCK_H

#include "../entities/entity.h"
#include <string>

namespace game {

    class block : public object {
    public:
        block();

        virtual ~block() noexcept = default;

        void setX(double dx);

        void setY(double dy);

    };
}


#endif //UPRUN_BLOCK_H