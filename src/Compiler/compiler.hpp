#pragma once


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

namespace Compiler {

struct CompilerWindowNode {
	const char* title;
	int x,y,w,h;
	Uint32 flag = SDL_WINDOW_SHOWN;
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
