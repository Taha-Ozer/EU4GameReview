#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <string>
#include "tokenizer.hpp"

class Parser
{
public:
    Parser(std::string filepath);
    EU4Value parseValue();

private:
    std::string path{};
    Tokenizer tokenizer;
};

#endif