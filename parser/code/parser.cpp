#include "../headers/types.hpp"
#include "../headers/parser.hpp"

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
        throw std::runtime_error("Syntax error, Wrong token"); // so we throw an error
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

    if (firstToken.type == TokenType::OPENBRACE)
    {
        // if it's an openbrace it's a list and we recursively call parseBlockOrList() again
        mode = ParseMode::LIST;
        EU4Value first_value = std::move(parseBlockOrList());
        list.push_back(std::make_unique<EU4Value>(std::move(first_value))); // we add the value to the EU4List
    }
    else if (firstToken.type == TokenType::STRING)
    {
        // if it's a string and the next an equals, it's a block
        if (tokenizer.peek().type == TokenType::EQUALS)
        {
            mode = ParseMode::BLOCK;
            tokenizer.getNextToken();
            EU4Value val = std::move(parseValue());                                          // we parse the value
            block.push_back({firstToken.value, std::make_unique<EU4Value>(std::move(val))}); // and add the key,value pair to the block
        }
        else
        {
            // if it's anything other than an equal sign, it means that we're in a list
            mode = ParseMode::LIST;
            list.push_back(std::make_unique<EU4Value>(std::move(firstToken.package()))); // we add the value to the list
        }
    }
    else
    {
        // all key-value pairs have strings as keys, if it's not a string. It means that we're IN a list
        mode = ParseMode::LIST;
        list.push_back(std::make_unique<EU4Value>(std::move(firstToken.package()))); // we add the value to the list
    }
    // until we come across a CLOSEBRACE token
    while (tokenizer.peek().type != TokenType::CLOSEBRACE)
    {
        // if we have a block
        if (mode == ParseMode::BLOCK)
        {
            // we get the next token
            Token key_token{tokenizer.getNextToken()};
            tokenizer.getNextToken();                                                       // we consume the EQUAL token
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

    // and until we hit the end of the file (END token)
    while (tokenizer.peek().type != TokenType::END)
    {
        // we get the keyToken
        Token key_token{tokenizer.getNextToken()};
        tokenizer.getNextToken();                                                       // consume the equal
        EU4Value val = std::move(parseValue());                                         // and parse its value
        block.push_back({key_token.value, std::make_unique<EU4Value>(std::move(val))}); // and push the pair
    }
    return block; // and return it
}
