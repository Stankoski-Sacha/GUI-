#pragma once

#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

// Types of tokens

namespace Compiler {
enum class TokenType {
  WINDOW,
  LBRACE,
  RBRACE,
  INDENTIFIER,
  DOT,
  EndOfFile,
  NUMBER,
  STRING,
  SEMICOLON,
  COMMA,
};

struct Token {
  TokenType token;
  std::string token_str_literal;
};

class Lexer {
public:
  std::vector<Token> transformingFile(const std::string& file_loc) {}
};
} // namespace Compiler
