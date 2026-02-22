#pragma once 

#include <iostream>
#include <vector>
#include <string>
#include <format>

// Other import 
#include "compiler.hpp"

namespace CODEGEN {
class Code_Gen {
private:
	Compiler::CompilerComponentNode componants;
		
	std::string upBoilerPlateCode() {
		return std::format("#include <SDL2/SDL.h>\n"
				"int main(int argc, char** argv) {{\n");
	};

	std::string makeWindowCode() {
		return std::format("SDL_Window* win = SDL_CreateWindow(\"{}\", {}, {}, {}, {}, {});\n" 
				"SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED)\n;",
				componants.win.title, componants.win.x, componants.win.y, componants.win.w, 
				componants.win.h, componants.win.flag
		);
	}


public:
	explicit Code_Gen(Compiler::CompilerComponentNode node) : componants(node) {}

	std::string make_final_code() {
		std::string code = "";

		code += upBoilerPlateCode();
		code += makeWindowCode();
		
				
		return code;
	}
};
}
