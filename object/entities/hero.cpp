//
// Created by otm on 22.04.17.
//

#include "hero.h"


namespace game {

    hero::hero() :
            _coins(0),
            _lifes(2) {}

    const unsigned int hero::getCoins() const {
        return _coins;
    }

    const uint16_t hero::getLifes() const {
        return _lifes;
    }

    void hero::increaseCoins() {
        ++_coins;
    }

    void hero::decreaseLifes() {
        if (_lifes > 0){
            --_lifes;
        }
    }

    void hero::increaseLifes() {
        ++_lifes;
    }
}