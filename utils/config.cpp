//
// Created by otm on 22.04.17.
//

#include <fstream>
#include <iostream>
#include "config.h"

game::config::config() :
        _winTitle("Up Run"),
        _videoMode(768, 800),
        _style(sf::Style::Default),
        _menuFPSLimit(60),
        _gameFPSLimit(240),
        _vSync(false) {
    try {
        //getFromFile();
    }
    catch (game::error::configFileReadError &) {}
}

void game::config::putInFile() noexcept {
    std::ofstream fileOut("config.bin", std::ios::binary | std::ios::out);
    fileOut.exceptions(std::ios::failbit | std::ios::badbit);

    try {
        fileOut.write((char *) (this), sizeof(*this));
    }
    catch (std::ios::failure &e) {
        //logging
        std::cerr << e.what() << std::endl;
    }

}

void game::config::getFromFile() throw(game::error::configFileReadError) {
    std::ifstream fileIn("config.bin", std::ios::binary | std::ios::in);
    if (fileIn.is_open()) {
        fileIn.exceptions(std::ios::failbit | std::ios::badbit);

        try {
            config temp;
            fileIn.read((char *) &temp, sizeof(temp));
            *this = temp;
        }
        catch (std::ios::failure &e) {
            throw game::error::configFileReadError("Config file is not found or corrupted");
        }
    }
}

game::config &game::config::operator=(const game::config &rhs) {
    _winTitle = rhs._winTitle;
    _style = rhs._style;
    _videoMode = rhs._videoMode;
    _menuFPSLimit = rhs._menuFPSLimit;
    _gameFPSLimit = rhs._gameFPSLimit;

    return *this;
}

game::config::~config() noexcept {
    putInFile();
}

const std::string &game::config::getWinTitle() const noexcept {
    return _winTitle;
}

const sf::VideoMode &game::config::getVideoMode() const noexcept {
    return _videoMode;
}

const std::uint32_t game::config::getStyle() const noexcept {
    return _style;
}

void game::config::resizeWindow(const unsigned int width, const unsigned int height) {
    _videoMode.width = width;
    _videoMode.height = height;
}

const unsigned short int game::config::getMenuFPSLimit() const noexcept {
    return _menuFPSLimit;
}

const unsigned short int game::config::getGameFPSLimit() const noexcept {
    return _gameFPSLimit;
}

void game::config::setGameFPSLimit(const unsigned short int newFPS) noexcept {
    _gameFPSLimit = newFPS;
}

const bool game::config::getVSync() const noexcept {
    return _vSync;
}

void game::config::setVSync(const bool newVSync) noexcept {
    _vSync = newVSync;
}

