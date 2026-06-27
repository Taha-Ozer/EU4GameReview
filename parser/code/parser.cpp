#include "../headers/types.hpp"
#include "../headers/parser.hpp"

// Constructor
Parser::Parser(std::string filepath) : path(filepath), tokenizer(filepath) {};

EU4Value Parser::parseValue()
{
    Token token = tokenizer.getNextToken();

    switch (token.type)
    {
    case TokenType::CLOSEBRACE:
    case TokenType::EQUALS:
    case TokenType::END:
        throw std::runtime_error("Syntax error, Wrong token");
    case TokenType::OPENBRACE:
        return parseBlockOrList();
    default:
        return EU4Value{token.value};
    }
}