#include "../headers/tokenizer.hpp"
#include <algorithm>

Token::Token(std::string value, TokenType type) : value{value}, type{type} {};

Tokenizer::Tokenizer(std::string path) : path{path}, reader(path) {};

Token Tokenizer::getNextToken()
{
    std::string tokenData{};
    int dot_counter{};
    while (true)
    {
        int next_character = reader.getNextCharacter();
        switch (next_character)
        {
        case '{':
            if (tokenData.length() != 0)
            {
                return classifyToken(tokenData, dot_counter);
            }
            return Token(tokenData, TokenType::OPENBRACE);
        case '}':
            if (tokenData.length() != 0)
            {
                return classifyToken(tokenData, dot_counter);
            }
            return Token(tokenData, TokenType::CLOSEBRACE);
        case '=':
            if (tokenData.length() != 0)
            {
                return classifyToken(tokenData, dot_counter);
            }
            return Token(tokenData, TokenType::EQUALS);
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            if (tokenData.length() != 0)
            {
                return classifyToken(tokenData, dot_counter);
            }
            continue;
        case '"':
            while (reader.peek() != '"' && reader.peek() != EOF)
            {
                tokenData.push_back(reader.getNextCharacter());
            }
            reader.getNextCharacter();
            return Token(tokenData, TokenType::STRING);
        case EOF:
            return Token(tokenData, TokenType::END);
        default:
            tokenData.push_back(next_character);
            if (next_character == '.')
            {
                dot_counter++;
            }
        }
    }
}

Token Tokenizer::classifyToken(std::string data, int dots)
{
    auto has_letters = [](const std::string &str)
    {
        return std::any_of(str.begin(), str.end(), [](unsigned char c)
                           { return std::isalpha(c); });
    };
    if (dots == 2)
    {
        return Token(data, TokenType::DATE);
    }
    else if (dots == 1)
    {
        return Token(data, TokenType::FLOAT);
    }
    else if (has_letters(data))
    {
        if (!data.compare("yes") || !data.compare("no"))
        {
            return Token(data, TokenType::BOOL);
        }
        return Token(data, TokenType::STRING);
    }
    else
    {
        return Token(data, TokenType::INT);
    }
}

Token Tokenizer::peek()
{
}