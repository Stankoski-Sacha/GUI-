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
				"SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);\n"
				"bool running = true;\n SDL_Event e;\n",
				componants.win.title, componants.win.x, componants.win.y, componants.win.w, 
				componants.win.h, componants.win.flag
		);
	}

	std::string renderLoopCodeStart() {
		return std::format("while (running) {{ \n"
				" while (SDL_PollEvent(&e)) {{ \n"
				"if (e.type == SDL_QUIT) {{ \n"
				"running = false;\n"
				"}}\n"
				"}}\n"
				"SDL_SetRenderDrawColor(ren, 255,255,255,255);\n"
				"SDL_RenderClear(ren);\n"
		);
	}

	std::string renderLoopCodeEnd() {
		return std::format("SDL_RenderPresent(ren);\n"
				"SDL_Delay(16);\n"
				"}}\n"
		);
	}

	std::string cleanupCode() {
		return std::format("SDL_DestroyWindow(win);\n"
				"SDL_DestroyRenderer(ren);\n"
				"SDL_Quit();\n"
				"return 0;\n"
				"}}\n"
		);
	}


public:
	explicit Code_Gen(Compiler::CompilerComponentNode node) : componants(node) {}

	std::string make_final_code() {
		std::string code = "";

		code += upBoilerPlateCode();
		code += makeWindowCode();
		code += renderLoopCodeStart();

		// Add code for render button etc not now 

		code += renderLoopCodeEnd();

		// End of the file 
		code += cleanupCode();
		return code;
	}
};
}
