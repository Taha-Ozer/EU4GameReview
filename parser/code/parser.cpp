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

EU4Value Parser::parseBlockOrList()
{
    ParseMode mode{};
    EU4Block block{};
    EU4List list{};

    Token firstToken{tokenizer.getNextToken()};

    if (firstToken.type == TokenType::OPENBRACE)
    {
        mode = ParseMode::LIST;
        EU4Value first_value = parseBlockOrList();
        list.push_back(std::make_unique<EU4Value>(first_value));
    }
    else if (firstToken.type == TokenType::STRING)
    {
        if (tokenizer.peek().type == TokenType::EQUALS)
        {
            mode = ParseMode::BLOCK;
            tokenizer.getNextToken();
            EU4Value val = parseValue();
            block.push_back({firstToken.value, std::make_unique<EU4Value>(val)});
        }
        else
        {
            mode = ParseMode::LIST;
            list.push_back(std::make_unique<EU4Value>(firstToken.value));
        }
    }
    else
    {
        mode = ParseMode::LIST;
        list.push_back(std::make_unique<EU4Value>(firstToken.value));
    }
    while (tokenizer.peek().type != TokenType::END)
    {
        if (mode == ParseMode::BLOCK)
        {
            Token key_token{tokenizer.getNextToken()};
            tokenizer.getNextToken();
            EU4Value val{parseValue()};
            block.push_back({key_token.value, std::make_unique<EU4Value>(val)});
        }
        else
        {
            EU4Value val{parseValue()};
            list.push_back(std::make_unique<EU4Value>(val));
        }
    }
    tokenizer.getNextToken();

    if (mode == ParseMode::BLOCK)
    {
        return EU4Value{block};
    }
    else
    {
        return EU4Value{list};
    }
    return EU4Value{};
}