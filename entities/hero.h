//
// Created by otm on 22.04.17.
//

#ifndef UPRUN_HERO_H
#define UPRUN_HERO_H


#include "entity.h"

namespace game{
    class hero: public entity {
    public:
        hero();

        hero(const std::string& newName);

        //virtual hero(const hero& rhs) = default;

        virtual ~hero() noexcept = default;

    private:

    };
}



#endif //UPRUN_HERO_H
