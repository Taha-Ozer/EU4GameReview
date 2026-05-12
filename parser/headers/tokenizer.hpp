#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include "reader.hpp"

enum class TokenType
{
    OPENBRACE,
    CLOSEBRACE,
    EQUALS,
    STRING,
    INT,
    FLOAT,
    DATE,
    BOOL,
    END
};

struct Token
{
    TokenType type;
    std::string value;
};

class Tokenizer
{
public:
    Tokenizer(std::string path);
    Token getNextToken();
    Token peek();

private:
    std::string path;
    Reader reader;
};

#endif