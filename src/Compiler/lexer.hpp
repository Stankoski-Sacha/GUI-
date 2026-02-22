#pragma once

#include <cctype>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

// Types of tokens

namespace Compiler {
enum class LexerTokenType {
  // Literals
  IDENTIFIER,
  INT_LITERAL,
  STRING_LITERAL,

  // Delimeters
  LEFT_BRACE,
  RIGHT_BRACE,
  COLON,
  SEMICOLON,
  COMMA,

  // Before INDENTIFIER
  DOT,

  // Special
  EndOfFile,
  WTF,
};

struct LexerToken {
  LexerTokenType type;
  std::string lexeme;

  friend std::ostream& operator<<(std::ostream& os, const LexerToken t) {
    return os << t.lexeme << '\n';
  }
};

class Lexer {
private:
public:
  std::vector<LexerToken> lexer_transform_to_tokens(const std::string& file_loc) {
    std::fstream file(file_loc);
    std::string word;
    std::string parsed{};

    // Get the text from the file into a std::string
    while (std::getline(file, word)) {
      parsed += word + ' ';
    }

    std::vector<LexerToken> tokens{};
    std::size_t i = 0;

    while (i < parsed.length()) {
      char current = parsed[i];

      if (std::isspace(current)) {
        i++;
        continue;
      }

      if (std::isalpha(current)) {
        std::size_t start = i;
        while (i < parsed.length() && std::isalnum(parsed[i])) {
          i++;
        }

        std::string identifier = parsed.substr(start, i - start);
        tokens.emplace_back(LexerToken{LexerTokenType::IDENTIFIER, identifier});
        continue;
      }

      if (std::isdigit(current)) {
        std::size_t start = i;

        while (i < parsed.length() && std::isdigit(parsed[i])) {
          i++;
        }
        std::string num = parsed.substr(start, i - start);
        tokens.emplace_back(LexerToken{LexerTokenType::INT_LITERAL, num});
        continue;
      }

      if (current == '"') {
        std::size_t start = i + 1; // To have the text and not the "
        i++;

        while (i < parsed.length() && parsed[i] != '"') {
          i++;
        }

        std::string strLiteral = parsed.substr(start, i - start);
        tokens.emplace_back(LexerToken{LexerTokenType::STRING_LITERAL, strLiteral});
        continue;
      }

      if (current == '{') {
        tokens.emplace_back(LexerToken{LexerTokenType::LEFT_BRACE, "{"});
        i++;
        continue;
      }

      if (current == '.') {
        tokens.emplace_back(LexerToken{LexerTokenType::DOT, "."});
        i++;
        continue;
      }

      if (current == '}') {
        tokens.emplace_back(LexerToken{LexerTokenType::RIGHT_BRACE, "}"});
        i++;
        continue;
      }

      if (current == ':') {
        tokens.emplace_back(LexerToken{LexerTokenType::COLON, ":"});
        i++;
        continue;
      }

      if (current == ',') {
        tokens.emplace_back(LexerToken{LexerTokenType::COMMA, ","});
        i++;
        continue;
      }

      if (current == ';') {
        tokens.emplace_back(LexerToken{LexerTokenType::SEMICOLON, ";"});
        i++;
        continue;
      }

      // End
      else {
        tokens.emplace_back(LexerToken{LexerTokenType::WTF, "?"});
        i++;
        continue;
      }
    }

    return tokens;
  }
};
} // namespace Compiler
