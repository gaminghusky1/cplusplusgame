cmake_minimum_required(VERSION 3.30)
project(cplusplusgame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "/opt/homebrew")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(cplusplusgame main.cpp)

target_link_libraries(cplusplusgame SDL2 SDL2main)
target_link_libraries(cplusplusgame SDL2 SDL2_image)
target_link_libraries(cplusplusgame SDL2 SDL2_gfx)