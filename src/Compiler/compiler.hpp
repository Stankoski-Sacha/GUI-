#pragma once


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

namespace Compiler {

struct CompilerWindowNode {
	const char* title = "GUI++"; // Default title to be changed by the user 
	int x,y,w,h; // Must indicate all of these during window creation 
	Uint32 flag = SDL_WINDOW_SHOWN; // Default flags maybe a TODO to make so that the user can choose custom flags 
};

struct CompilerComponentNode {
	CompilerWindowNode win;
};



class compiler {
private:
	CompilerWindowNode makeWindow() {
		CompilerWindowNode window;
		//TODO 
		
		return window;
	}

public:
	compiler() = default;

	CompilerComponentNode makeNode() {
		CompilerComponentNode node{};
		//TODO
		

		return node;
	}


};
}
