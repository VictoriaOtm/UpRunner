cmake_minimum_required(VERSION 3.7)
project(UpRun)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp entities/entity.cpp entities/entity.h gui/gui.cpp gui/gui.h Game.cpp Game.h utils/config.cpp utils/config.h utils/exceptions.h entities/hero.cpp entities/hero.h entities/views/heroView.cpp entities/views/heroView.h)
add_executable(UpRun ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(UpRun ${SFML_LIBRARIES})
endif ()