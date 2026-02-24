#pragma once

/*
 * Assume everything that doesn't have a optional is mandatory to include
 * in code.
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Lexer part
#include "lexer.hpp"

namespace Parser {
struct ASTNODE {
	virtual ~ASTNODE() = default;
	virtual std::string toString() const = 0;

};

using NodePtr =  std::unique_ptr<ASTNODE>;

struct Number : ASTNODE {
	int value;

	explicit Number(int value) : value(value) {}

	std::string toString() const override { 
		return std::to_string(value);
	}
}; 

struct Identifier : ASTNODE{};


class Parser {
private:
	std::vector<Lexer::Token> lexer_tokens;
public:
	explicit Parser(std::vector<Lexer::Token> tok) : lexer_tokens(tok) {};

	
};
} // namespace Compiler
