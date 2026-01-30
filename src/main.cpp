#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <vector>

// Compiler part
#include "Compiler/lexer.hpp"
#include "Compiler/parser.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "GUI++ : Error too few argument" << '\n';
    return 1;
  }

  using namespace std; // <- don't worry about it, it's not a bad thing

  optional<string> filename = nullopt;
  // TODO LATER -> optional<string> output = std::nullopt;

  // GUI++ main.gui -o app
  // GUI++ main.gui -> default name to a.out or the file name

  for (auto i{1}; i <= argc - 1; i++) {
    auto searchfile = string(argv[i]).find(".gui");

    if (searchfile != string::npos) {
      filename = argv[i];
    }
  }

  if (filename == nullopt) {
    cerr << "GUI++ : Error no source file found" << endl;
    cerr << "Compilation Stopped" << endl;
    return 1;
  }

  ifstream file(*filename);
  string word;
  string parsed;

  while (std::getline(file, word)) {
    parsed += word;
  }

  vector<string> parsed2{};
  std::istringstream oss(parsed);
  while (oss >> word) {
    parsed2.emplace_back(word);
  }

  for (const auto& i : parsed2) {
    std::cout << i << '\n';
  }
}
