cmake_minimum_required(VERSION 3.28)
project(GUIPlusPlus)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find SDL2 packages
find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(guipp
	src/main.cpp
       	src/Compiler/compiler.hpp
	src/Compiler/lexer.hpp
	src/Compiler/parser.hpp
	src/Compiler/code_gen.hpp
	src/GUI_Componants/Button.hpp	
)

set_target_properties(guipp PROPERTIES
	OUTPUT_NAME "GUI++"
)

# Link SDL2 libraries
target_link_libraries(guipp
  PRIVATE
    SDL2::SDL2
    SDL2_ttf::SDL2_ttf
)
