#include <cmath>
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
#include "Compiler/compiler.hpp"
#include "Compiler/code_gen.hpp"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "GUI++ : Error too few argument" << '\n';
    return 1;
  }

  using namespace std; // <- don't worry about it, it's not a bad thing

  optional<string> filename = nullopt;
  optional<string> outputname = nullopt;
  // TODO LATER -> optional<string> output = nullopt;

  // GUI++ main.gui -o app
  // GUI++ main.gui -> default name to a.out or the file name

  for (auto i{1}; i <= argc - 1; i++) {
    auto searchfile = string(argv[i]).find(".gui");
    auto output_token = string(argv[i]).find("-o");

    if (searchfile != string::npos) {
      filename = argv[i];
    }
  }


  if (filename == nullopt) {
    cerr << "GUI++ : Error no source file found" << endl;
    cerr << "Compilation Stopped" << endl;
    return 1;
  }

  Compiler::Lexer lex{};
  auto lexer_tok = lex.lexer_transform_to_tokens(*filename);
  for (const auto& i : lexer_tok) {
	  cout << i << endl;
  }

  Compiler::Parser parser = Compiler::Parser(lexer_tok);
	
  
}
