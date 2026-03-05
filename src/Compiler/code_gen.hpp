#pragma once 

#include <cwchar>
#include <iostream>
#include <vector>
#include <string>
#include <format>
#include <fstream>

// Other import 
#include "compiler.hpp"

namespace CODEGEN {
class Code_Gen {
private:
	Compiler::ComponentNode componants;
		
	// The boilerplate of including headers
	std::string headerCode() {
		return std::format("#include <SDL2/SDL.h>\n"
				"#include <SDL2/SDL_ttf.h>\n"
				"#include <string>\n"
		);
					
	};

	std::string mainFunctionEntry() {
		return std::format("int main(int argc, char** argv) {{\n");
	}

	std::string initCode() {
		return std::format("	SDL_Init(SDL_INIT_EVERYTHING);\n"
				   "	TTF_Init();\n"
		);
	}

	std::string makeWindowCode() {
		return std::format("	SDL_Window* win = SDL_CreateWindow(\"{}\", {}, {}, {}, {}, {});\n" 
				"	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);\n"
				"	bool running = true;\n        SDL_Event e;\n",
				componants.win.title.c_str(), componants.win.x, componants.win.y, componants.win.w, 
				componants.win.h, componants.win.flag
		);
	}

	std::string renderLoopCodeStart() {
		return std::format("	while (running) {{ \n"
				"		while (SDL_PollEvent(&e)) {{ \n"
				"			if (e.type == SDL_QUIT) {{ \n"
				"				running = false;\n"
				"			}}\n"
				"		}}\n"
				"		SDL_SetRenderDrawColor(ren, 255,255,255,255);\n"
				"		SDL_RenderClear(ren);\n"
		);
	}

	std::string renderLoopCodeEnd() {
		return std::format("		SDL_RenderPresent(ren);\n"
				"		SDL_Delay(16);\n"
				"	}}\n"
		);
	}

	std::string cleanupCode() {
		return std::format("	SDL_DestroyWindow(win);\n"
				"	SDL_DestroyRenderer(ren);\n"
				"	TTF_CloseFont(font);\n"
				"	SDL_Quit();\n"
				"	TTF_Quit();\n"
				"	return 0;\n"
				"}}\n"
		);
	}

	// Add the class button to the code before main 
	std::string addButtonCode() {
		std::ifstream file(std::string(PROJECT_SOURCE_DIR) + "/src/GUI_Componants/Button.hpp");
		

		std::string button_code;
		std::string word;

		while (std::getline(file, word)) {
			button_code += word + '\n';
		}

		return button_code;
	}
	
	std::string addTextBoxCode() {
		std::ifstream file(std::string(PROJECT_SOURCE_DIR) + "/src/GUI_Componants/TextBox.hpp");

		std::string textboxCode, word;

		while (std::getline(file, word)) {
			textboxCode += word + '\n';
		}

		return textboxCode;
	}

	std::string makeButtonInitCode(int buttonID) {
		return std::format("Button b{} = Button({}, {}, {}, {}, \"{}\", font);\n",
				buttonID,
				componants.buttonsCreated[buttonID].x ,
				componants.buttonsCreated[buttonID].y ,
				componants.buttonsCreated[buttonID].w ,
				componants.buttonsCreated[buttonID].h ,
				componants.buttonsCreated[buttonID].buttonText
		);
	}

	std::string makeButtonRenderCode(int buttonID) {
		return std::format("b{}.render(ren);\n", buttonID);
	}

	std::string embedFontCode() {
	    std::ifstream src(std::string(PROJECT_SOURCE_DIR) + "/font/LiberationSans-Regular.ttf", std::ios::binary);
	    if (!src.is_open()) {
		std::cerr << "Could not find arial.ttf\n";
		return "";
	    }
	    std::ofstream dst("arial.ttf", std::ios::binary);
	    dst << src.rdbuf();
	    return "";
	}

	std::string openFontCode() {
		return "TTF_Font* font = TTF_OpenFont(\"LiberationSans-Regular.ttf\", 20);\n";
	}


public:
	explicit Code_Gen(Compiler::ComponentNode node) : componants(node) {}

	std::string make_final_code() {
		std::string code = "";
		code += headerCode();
		int buttons = -1, textboxes = -1;

		// Check for any componant 
		if (not componants.buttonsCreated.empty()) {
			code += addButtonCode();
			buttons = componants.buttonsCreated.size() - 1;
		}

		if (not componants.TextBoxCreated.empty()) {
			code += addTextBoxCode();
			textboxes = componants.TextBoxCreated.size() - 1;
		}

		// Start of the code 
		code += mainFunctionEntry();
		code += initCode();
		code += makeWindowCode();
		code += openFontCode();
		
		// GUI Comp init here 
		int bTemp = buttons;
		while (bTemp >= 0) {
			code += makeButtonInitCode(bTemp);
			bTemp--;
		}

		code += renderLoopCodeStart();

		// Add code for render button etc not now 
		bTemp = buttons;
		while (bTemp >= 0) {
			code += makeButtonRenderCode(bTemp);
			bTemp--;
		}
		code += renderLoopCodeEnd();

		// End of the file 
		code += cleanupCode();
		return code;
	}
};
}
