#include "../headers/tokenizer.hpp"
#include <algorithm>

// Token and Tokenizer constructors
Token::Token(std::string value, TokenType type) : value{value}, type{type} {};

Tokenizer::Tokenizer(std::string path) : path{path}, reader(path) {};

Token Tokenizer::getNextToken()
{
    std::string tokenData{}; // we build the token here (might change later for optimization)
    int dot_counter{};       // dot counter per token (helps detecting the tokentype)
    while (true)
    {
        int next_character = reader.getNextCharacter();
        /*
        throughout the function we have a classifyToken function.
        This is used to return existing tokens if we come across a new tokentype
        we specify the tokentype with this and return it.
        We also have to put back the fetched character back into the istream to not lose it.
        see classifyToken() for extra info.
        */
        switch (next_character)
        {
        case '{': // if it's a brace opening
            if (tokenData.length() != 0)
            {
                reader.putback(next_character);
                return classifyToken(tokenData, dot_counter);
            }
            return Token(tokenData, TokenType::OPENBRACE);
        case '}': // brace closing
            if (tokenData.length() != 0)
            {
                reader.putback(next_character);
                return classifyToken(tokenData, dot_counter);
            }
            return Token(tokenData, TokenType::CLOSEBRACE);
        case '=': // equal sign
            if (tokenData.length() != 0)
            {
                reader.putback(next_character);
                return classifyToken(tokenData, dot_counter);
            }
            return Token(tokenData, TokenType::EQUALS);
        // if they're white spaces
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            if (tokenData.length() != 0)
            {
                return classifyToken(tokenData, dot_counter);
            }
            continue;
        // if it's a quote
        case '"':
            // we have to keep reading as it's a quoted string
            while (reader.peek() != '"' && reader.peek() != EOF)
            {
                tokenData.push_back(reader.getNextCharacter());
            }
            if (reader.peek() == '"')
            {
                tokenData.push_back(next_character); // if it's a unquote we add it.
            }
            else
            {
                throw std::runtime_error("Unexpected termination on quoted string"); // if it's an EOF, we can't make up data so we throw an exception
            }
            return Token(tokenData, TokenType::STRING);
        case EOF:                                    // if it's the end  of the file
            return Token(tokenData, TokenType::END); // return an END token
        default:
            // default we push the char in the string
            // and eventually increment the dotcounter if it's a period
            tokenData.push_back(next_character);
            if (next_character == '.')
            {
                dot_counter++;
            }
        }
    }
}

// Token classifier
Token Tokenizer::classifyToken(std::string data, int dots)
{
    // lambda function to check for letters (not numbers) inside the string
    auto has_letters = [](const std::string &str)
    {
        return std::any_of(str.begin(), str.end(), [](unsigned char c)
                           { return std::isalpha(c); });
    };
    // if there are 2 dots it's a date (xx.xx.xxxx)
    if (dots == 2)
    {
        return Token(data, TokenType::DATE);
    }
    // if there is 1 dot, it's a float (x.yyyyyy)
    else if (dots == 1)
    {
        return Token(data, TokenType::FLOAT);
    }
    // if it has letters, it could either be a bool or a string
    else if (has_letters(data))
    {
        // if it's a "yes" or a "no" it's a bool
        if (!data.compare("yes") || !data.compare("no"))
        {
            return Token(data, TokenType::BOOL);
        }
        // otherwise it's a string
        return Token(data, TokenType::STRING);
    }
    // if it's none of it, it's an integer
    else
    {
        return Token(data, TokenType::INT);
    }
}

Token Tokenizer::peek()
{
}