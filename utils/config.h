#ifndef UPRUN_CONFIG_H
#define UPRUN_CONFIG_H

#include <SFML/Window.hpp>
#include "exceptions.h"

namespace game {
    class config {
    public:
        config();

        ~config() noexcept;

        config &operator=(const config &rhs);

        const std::string& getWinTitle() const noexcept;

        const sf::VideoMode& getVideoMode() const noexcept;

        const std::uint32_t getStyle() const noexcept;

        const unsigned short int getMenuFPSLimit() const noexcept;

        const unsigned short int getGameFPSLimit() const noexcept;

        const bool getVSync() const noexcept;

        void setVSync(const bool newVSync) noexcept;

        void setGameFPSLimit(const unsigned short int newFPS) noexcept;

        void putInFile() noexcept;

        void getFromFile() throw(game::error::configFileReadError);

        void resizeWindow(const unsigned int width, const unsigned int height);

//    config(const config& rhs);

    private:
        std::string _winTitle;
        sf::VideoMode _videoMode;
        std::uint32_t _style;

        unsigned short int _menuFPSLimit;
        unsigned short int _gameFPSLimit;

        bool _vSync;
    };
}


#endif //UPRUN_CONFIG_H
