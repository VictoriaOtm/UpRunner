cmake_minimum_required(VERSION 3.6.3)
project(UpRun)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp object/entities/entity.cpp object/entities/entity.h interface/gui/gui.cpp interface/gui/gui.h Game.cpp Game.h utils/config.cpp utils/config.h utils/exceptions.h object/entities/hero.cpp object/entities/hero.h object/entities/views/heroView.cpp object/entities/views/heroView.h map/Map.cpp map/Map.h object/block/block.cpp object/block/block.h object/block/blockView/blockView.cpp object/block/blockView/blockView.h object/object.cpp object/object.h interface/menu/menu.cpp interface/menu/menu.h interface/menu/basicMenu.cpp interface/menu/basicMenu.hpp interface/menu/settingsMenu.cpp interface/menu/settingsMenu.hpp)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-long-long -pedantic")
add_executable(UpRun ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(UpRun ${SFML_LIBRARIES})
endif ()

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()