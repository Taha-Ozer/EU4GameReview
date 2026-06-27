#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <string>
#include "tokenizer.hpp"

enum class ParseMode
{
    LIST,
    BLOCK
};

class Parser
{
public:
    Parser(std::string filepath);
    EU4Block parseFile();
    EU4Value parseValue();
    EU4Value parseBlockOrList();

private:
    std::string path{};
    Tokenizer tokenizer;
};

#endif