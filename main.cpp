#include <iostream>
#include "Game.h"

int main() {
    game::Game app;

    try{
        app.run();
    }
    catch (std::runtime_error& e){
        //logging
        std::cout << e.what();
    }
    return 0;
}