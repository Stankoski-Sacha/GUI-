#pragma once


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <optional>

namespace Compiler {

struct WindowNode {
	const char* title; // Default title to be changed by the user 
	int x,y,w,h; // Must indicate all of these during window creation 
	Uint32 flag = SDL_WINDOW_SHOWN; // Default flags maybe a TODO to make so that the user can choose custom flags 

	WindowNode() = default;

	WindowNode(std::string t, int x, int y, int w, int h) : 
		title(t.c_str()), x(x), y(y), w(w), h(h) {}

	WindowNode(int x, int y, int w, int h) : 
		title("GUI++"), x(x), y(y), w(w), h(h) {}

};

struct Button {
	const char* buttonText; // Default text to 'button'
	int x, y, w, h; // Mandatory to put
	
	Button() = default;

	Button(std::string text, int x, int y, int w, int h) :
		buttonText(text.c_str()), x(x), y(y), w(w), h(h) {}

	Button(int x, int y, int w, int h) :
		buttonText("button"), x(x), y(y), w(w), h(h) {}

};

struct TextBox {
	const char* defaultText; // Default text to a blank space ' '
	int x, y, w, h; // Mandatory to put 
	bool isEditable; // Also mandatory 
	
	TextBox() = default;

	TextBox(std::string text, int x, int y, int w, int h, bool edit) :
		defaultText(text.c_str()), x(x), y(y), w(w), h(h), isEditable(edit) {}

	TextBox(int x, int y, int w, int h, bool edit) :
		defaultText(" "), x(x), y(y), w(w), h(h), isEditable(edit) {}

};


struct ComponentNode {
	WindowNode win;
	std::vector<Button> buttonsCreated;
	std::vector<TextBox> TextBoxCreated;
};


class compiler {
private:
	WindowNode makeWindow() {
		WindowNode window{};

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
