#pragma once


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

namespace Compiler {

struct WindowNode {
	const char* title = "GUI++"; // Default title to be changed by the user 
	int x,y,w,h; // Must indicate all of these during window creation 
	Uint32 flag = SDL_WINDOW_SHOWN; // Default flags maybe a TODO to make so that the user can choose custom flags 
};

struct ComponentNode {
	WindowNode win;
};



class compiler {
private:
	WindowNode makeWindow() {
		WindowNode window;
		//TODO 
		
		return window;
	}

public:
	compiler() = default;

	ComponentNode makeNode() {
		ComponentNode node{};
		//TODO
		

		return node;
	}


};
}
