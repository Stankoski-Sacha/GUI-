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

namespace Compiler {
struct ASTNODE {
	virtual ~ASTNODE();
};

class Parser {
private:
	std::vector<LexerToken> lexer_tokens;
public:
	explicit Parser(std::vector<LexerToken> tok) : lexer_tokens(tok) {};

	
};
} // namespace Compiler
