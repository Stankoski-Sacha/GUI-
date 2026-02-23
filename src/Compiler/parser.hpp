#pragma once

/*
 * Assume everything that doesn't have a optional is mandatory to include
 * in code.
 */

#include <iostream>
#include <string>
#include <vector>

// Lexer part
#include "lexer.hpp"

namespace Parser {
struct ASTNODE {
	virtual ~ASTNODE();
};

class Parser {
private:
	std::vector<Lexer::Token> lexer_tokens;
public:
	explicit Parser(std::vector<Lexer::Token> tok) : lexer_tokens(tok) {};

	
};
} // namespace Compiler
