cmake_minimum_required(VERSION 3.28)
project(GUIPlusPlus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(guipp)

target_sources(guipp
  PRIVATE
    src/Compiler/main.cpp
  PUBLIC
    FILE_SET CXX_MODULES FILES
      src/Compiler/lexer.cppm
      src/Compiler/compiler.cppm
      src/Compiler/parser.cppm
      src/GUI_Componants/window.cppm
      src/GUI_Componants/Component.cppm
)

# Link SDL2 libraries
target_link_libraries(guipp
  PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)
