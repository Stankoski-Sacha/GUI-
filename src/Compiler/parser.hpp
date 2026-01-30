#pragma once

/*
 * Assume everything that doesn't have a optional is mandatory to include
 * in code.
 */

#include <iostream>
#include <string>
#include <vector>

namespace Compiler {
struct ASTNODE {
  virtual ~ASTNODE() = default;
};

struct DIMENSIONS {
  int w, h;
};

struct POSITION {
  int x, y;
};

struct DATABLOCK {
  std::optional<POSITION> pos;
  DIMENSIONS dimensions;
  std::optional<std::string> title;
  std::string id;
};

struct WINDOWNODE : ASTNODE {
  DATABLOCK data;
};

class Parser {
public:
};
} // namespace Compiler
