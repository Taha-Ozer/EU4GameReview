#include "../headers/types.hpp"
#include "../headers/parser.hpp"
#include <iostream>

// Constructor
Parser::Parser(std::string filepath) : path(filepath), tokenizer(filepath) {};

EU4Value Parser::parseValue()
{
    // we get the next token
    Token token = tokenizer.getNextToken();

    // we have to check which kind of token it is
    switch (token.type)
    {
    // the following cases are impossible to get as a value
    case TokenType::CLOSEBRACE:
    case TokenType::EQUALS:
    case TokenType::END:
        throw std::runtime_error(
            "Syntax error (parseValue): unexpected token of type " + std::to_string(static_cast<int>(token.type)) +
            " with value '" + token.value + "'"); // so we throw an error
    case TokenType::OPENBRACE:
        return parseBlockOrList(); // if it leads to another list, we call parseBlockOrList() again.
    default:
        return token.package(); // otherwise we return te value
    }
}

EU4Value Parser::parseBlockOrList()
{
    ParseMode mode{}; // this is to choose which kind of value we have
    // we initialize both block and list but only fill 1
    EU4Block block{};
    EU4List list{};

    Token firstToken{tokenizer.getNextToken()}; // we get the first token

    switch (firstToken.type) // we decide based on the type of the first token what will happen
    {
    case TokenType::CLOSEBRACE:
        return EU4Value{std::move(list)}; // if it's a closebrace, it's an empty list
    case TokenType::OPENBRACE:
    {
        mode = ParseMode::LIST;                                             // if it's an openbrace, we start a list
        EU4Value first_value = std::move(parseBlockOrList());               // we parse inside the list
        list.push_back(std::make_unique<EU4Value>(std::move(first_value))); // we add it to the list;
        break;
    }
    case TokenType::STRING:
    case TokenType::INT:
    case TokenType::DATE:
    case TokenType::BOOL:
    case TokenType::FLOAT:
        if (tokenizer.peek().type == TokenType::EQUALS)
        {
            // if the very next token is an equal sign, it's a block
            mode = ParseMode::BLOCK;
            Token eq = tokenizer.getNextToken();
            if (eq.type != TokenType::EQUALS)
            {
                throw std::runtime_error("Expected EQUALS after key '" + firstToken.value + "', got type " + std::to_string(static_cast<int>(eq.type)) + " value '" + eq.value + "'");
            }
            EU4Value val = std::move(parseValue());                                          // we parse the value
            block.push_back({firstToken.value, std::make_unique<EU4Value>(std::move(val))}); // and add the key,value pair to the block
        }
        else
        {
            // if it's anything other than an equal sign, it means that we're in a list
            mode = ParseMode::LIST;
            list.push_back(std::make_unique<EU4Value>(std::move(firstToken.package()))); // we add the value to the list
        }
        break;
    default:
        throw std::runtime_error("We can't have these types of tokens here");
    }

    // until we come across a CLOSEBRACE token
    while (tokenizer.peek().type != TokenType::CLOSEBRACE)
    {
        // if we have a block
        if (mode == ParseMode::BLOCK)
        {
            // we get the next token
            Token key_token{tokenizer.getNextToken()};
            Token eq = tokenizer.getNextToken();
            if (eq.type != TokenType::EQUALS)
            {
                throw std::runtime_error("Expected EQUALS after key '" + key_token.value + "', got type " + std::to_string(static_cast<int>(eq.type)) + " value '" + eq.value + "'");
            } // we consume the EQUAL token
            EU4Value val = std::move(parseValue());                                         // parse the next token
            block.push_back({key_token.value, std::make_unique<EU4Value>(std::move(val))}); // and add the pair to the block
        }
        else
        {
            // otherwise, we parse the next value
            EU4Value val = std::move(parseValue());
            list.push_back(std::make_unique<EU4Value>(std::move(val))); // and add it to the list
        }
    }
    tokenizer.getNextToken(); // we consume the CLOSEBRACE

    // and we return the EU4Value accordingly
    if (mode == ParseMode::BLOCK)
    {
        return EU4Value{std::move(block)};
    }
    else
    {
        return EU4Value{std::move(list)};
    }
}

EU4Block Parser::parseFile()
{
    // this is the main function for parsing the file
    EU4Block block{}; // we create a block

    if (tokenizer.peek().value == "EU4txt")
    {
        tokenizer.getNextToken();
    }

    // and until we hit the end of the file (END token)
    while (tokenizer.peek().type != TokenType::END)
    {
        // we get the keyToken
        Token key_token{tokenizer.getNextToken()};
        // and check if it's of wrong type of Token
        if (key_token.type == TokenType::OPENBRACE || key_token.type == TokenType::CLOSEBRACE ||
            key_token.type == TokenType::EQUALS || key_token.type == TokenType::END)
        {
            throw std::runtime_error("Expected a key, got type " + std::to_string(static_cast<int>(key_token.type)) + " value '" + key_token.value + "'");
        }
        Token eq = tokenizer.getNextToken(); // we check if the next token is an EQUAL
        if (eq.type != TokenType::EQUALS)
        {
            throw std::runtime_error("Expected EQUALS after key '" + key_token.value + "', got type " + std::to_string(static_cast<int>(eq.type)) + " value '" + eq.value + "'");
        }
        EU4Value val = std::move(parseValue());                                         // and parse its value
        block.push_back({key_token.value, std::make_unique<EU4Value>(std::move(val))}); // and push the pair
    }
    return block; // and return it
}
