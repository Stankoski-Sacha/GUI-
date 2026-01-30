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
  DATABLOCK,
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

Token toToken(const std::string t) {
  if (t == "Window") {
    return Token{TokenType::WINDOW, "Window"};
  }
  if (t == "data") {
  }
}

class Lexer {
public:
  std::vector<Token> transformingFile(const std::string& file_loc) {
    std::fstream file(file_loc);
    std::string word;
  }
};
} // namespace Compiler
