#pragma once


#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <any>
#include <utility>
#include <cctype>


// Includes 
#include "lexer.hpp"
#include "parser.hpp"

namespace Compiler {

enum class Context {
	WINDOW,
	TEXTBOX,
	BUTTON
};

struct WindowNode {
	std::string title = "Window"; // Default title to be changed by the user 
	int x,y,w,h; // Must indicate all of these during window creation 
	Uint32 flag = SDL_WINDOW_SHOWN; // Default flags maybe a TODO to make so that the user can choose custom flags 

	WindowNode() = default;
};

struct Button {
	std::string buttonText = " "; // Default text to 'button'
	int x, y, w, h; // Mandatory to put
	
	Button() = default;
};

struct TextBox {
	const char* defaultText = " "; // Default text to a blank space ' '
	int x, y, w, h; // Mandatory to put 
	bool isEditable; // Also mandatory 
	
	TextBox() = default;
};


// All componants inside of a struct to make it easier to move around
struct ComponentNode {
	WindowNode win;
	std::vector<Button> buttonsCreated;
	std::vector<TextBox> TextBoxCreated;
};


class compiler {
private:
	std::vector<Lexer::Token> toks;

	std::pair<int, int> returnVals(const std::vector<Lexer::Token>& toks) {
		std::pair<int, int> pair;

		int t1 = -1 ,t2 = -1;

		for (const auto& tokens: toks) {
			if (tokens.type == Lexer::TokenType::INT_LITERAL && t1 == -1) {
				t1 = std::stoi(tokens.lexeme);
			} else if (tokens.type == Lexer::TokenType::INT_LITERAL && t1 != -1) {
				t2 = std::stoi(tokens.lexeme);
			}
		}

		pair = std::make_pair(t1,t2);

		return pair;

	}

	WindowNode makeWindow(const std::vector<Lexer::Token>& toks) {
		using namespace Lexer;
		WindowNode node;

		std::pair<int, int> dimensionsPair;
		std::pair<int, int> positionPair;
		std::string title;
		for (auto i{0}; i < toks.size(); i++) {
			if (toks[i].type == TokenType::IDENTIFIER && toks[i].lexeme == "dimensions") {
				dimensionsPair = returnVals(std::vector<Token>{
					toks.begin(), std::find_if(toks.begin(), toks.end(), 
						[](const Token& tok) { return tok.type == TokenType::SEMICOLON; })});	
				do {
				       i++;
				} while (toks[i].type != TokenType::SEMICOLON);	       
			}
			else if (toks[i].type == TokenType::IDENTIFIER && toks[i].lexeme == "position") {
				positionPair = returnVals(std::vector<Token>{
					toks.begin(), std::find_if(toks.begin(), toks.end(), 
						[](const Token& tok) { return tok.type == TokenType::SEMICOLON; })});	
				do {
				       i++;
				} while (toks[i].type != TokenType::SEMICOLON);	       
			}
			else if (toks[i].type == TokenType::IDENTIFIER && toks[i].lexeme == "title") {
				do {
					i++;
				} while (toks[i].type != TokenType::STRING_LITERAL);

				title = toks[i].lexeme;

				do {
					i++;
				} while (toks[i].type != TokenType::SEMICOLON);	
			}
		}

		node.w = dimensionsPair.first;
		node.h = dimensionsPair.second;
		node.x = positionPair.first;
		node.y = positionPair.second;
		node.title = title;

		return node;
	}

	TextBox makeTextBox(const std::vector<Lexer::Token>& toks) {

	}

	Button makeButton(const std::vector<Lexer::Token>& toks) {

	}


public:
	explicit compiler(std::vector<Lexer::Token> tok) : toks(tok) {};

	ComponentNode makeNode() {
		ComponentNode node{};
		Context context;
		
		for (auto i{0}; i < toks.size(); i++) {
			switch (toks[i].type) {
			case Lexer::TokenType::IDENTIFIER:		
				if (toks[i].lexeme == "Window") {
					context = Context::WINDOW; 
				}
				if (toks[i].lexeme == "Button") {
					context = Context::BUTTON;
				}
				if (toks[i].lexeme == "TextBox") {
					context = Context::TEXTBOX;
				}
				if (toks[i].lexeme == "data") {
					auto data_end = std::find_if(
						toks.begin(), toks.end(),
						[](const Lexer::Token& token) {
							return token.type == Lexer::TokenType::RIGHT_BRACE;
					});
					// The data between the "{" and "}" of the .data 
					std::vector<Lexer::Token> subvec(toks.begin() + i + 1, data_end);	

					switch (context) {
						case Context::WINDOW:
							node.win = makeWindow(subvec);
							break;
						case Context::BUTTON:
							node.buttonsCreated.emplace_back(makeButton(subvec));
							break;
						case Context::TEXTBOX:
							node.TextBoxCreated.emplace_back(makeTextBox(subvec));
							break;
					}
				}
			default: continue;
			
 			}				 
		}
									
	

		return node;
	}


};
}
