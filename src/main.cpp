#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>

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
 // for (const auto& i : lexer_tok) {
//	  cout << i << endl;
 // }

  Compiler::Parser parser = Compiler::Parser(lexer_tok);
  
  Compiler::CompilerComponentNode code = {Compiler::CompilerWindowNode{"title", 100,100,100,100}};

  CODEGEN::Code_Gen gen{code};

  std::string final_SDL2_code = gen.make_final_code();

  // make a random generated name 
  mt19937 random_gen(random_device{}());
  string file_name{};
  uniform_int_distribution<int> dist(10,30);
  int size = dist(random_gen);

  for (int i{}; i <= size; i++) {
	  file_name += static_cast<char>(dist(random_gen) % 26 + 'a');
  }

  file_name += ".cpp";

  ofstream file(file_name); 
  // Temporary name, changing it later to random name 
  // to avoid collision if another file is the same name
  
  file << final_SDL2_code;
  file.close();

  std::string command = std::format("g++ {} -o {} -lSDL2", file_name, "output");

  system(command.c_str());

  // filesystem::remove(file_name);

  return 0;
}
