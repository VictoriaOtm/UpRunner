//
// Created by otm on 22.04.17.
//

#ifndef UPRUN_HERO_H
#define UPRUN_HERO_H


#include "entity.h"
#include <SFML/Audio.hpp>

namespace game{
    class hero: public entity {
    public:
        hero();

        //virtual hero(const hero& rhs) = default;

        virtual ~hero() noexcept = default;

        const unsigned int getCoins() const;

        const uint16_t getLifes() const;

        void increaseCoins();

        void decreaseLifes();

        void increaseLifes();

    private:
        unsigned int _coins;
        uint16_t _lifes;

        sf::SoundBuffer soundBuf;
        sf::Sound coinSound;
    };
}



#endif //UPRUN_HERO_H
