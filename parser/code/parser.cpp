#include "../headers/types.hpp"
#include "../headers/parser.hpp"

// Constructor
Parser::Parser(std::string filepath) : path(filepath), tokenizer(filepath) {};