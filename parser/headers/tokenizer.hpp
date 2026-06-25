#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP
#include <string>
#include "reader.hpp"

// There are a set amount of types of tokens we can have
// The enum under lists all of them.
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

// A token consists of the tokentype and the value as a string
struct Token
{
    Token(std::string value, TokenType type);
    TokenType type;
    std::string value{};
};

// the main tokenizer class
class Tokenizer
{
public:
    Tokenizer(std::string path);
    Token getNextToken(); // we get the next token
    Token peek();         // we peek at the next token

private:
    Token classifyToken(std::string data, int dots);
    std::string path; // it still has the path so it can make a reader member
    Reader reader;    // member readerclass
};

#endif