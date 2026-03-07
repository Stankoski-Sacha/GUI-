#pragma once

/*
 * The hard part :( 
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

struct String : ASTNODE {
	const char* val;

	explicit String(const char* v) : val(v) {}

	std::string toString() const override {
		return std::string(val);
	}
};

struct Identifier : ASTNODE{
	const char dotIdentifier;
	const char* idenName;

	explicit Identifier(char dot, const char* iden) : dotIdentifier(dot), idenName(iden) {}
	
	std::string toString() const override {
		return dotIdentifier + idenName;	
	}
};



class Parser {
private:
	std::vector<Lexer::Token> lexer_tokens;
public:
	explicit Parser(std::vector<Lexer::Token> tok) : lexer_tokens(tok) {};

	
};
} // namespace Compiler
