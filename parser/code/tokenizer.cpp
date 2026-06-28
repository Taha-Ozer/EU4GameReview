#include "../headers/tokenizer.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>

// Token and Tokenizer constructors
Token::Token(std::string value, TokenType type) : value{value}, type{type} {};

EU4Value Token::package() const
{
    // we check the type of the token
    /*
    The goal of this function is to package a token into its correct typed EU4Value
    That way the conversion doesn't have to happen inside the parser itself.
    */
    switch (type)
    {
    case TokenType::INT:
        return EU4Value{std::stoll(value)};
    case TokenType::BOOL:
        if (value == "yes")
        {
            return EU4Value{true};
        }
        else
        {
            return EU4Value{false};
        }
    case TokenType::FLOAT:
        return EU4Value{std::stof(value)};
    case TokenType::STRING:
        return EU4Value{value};
    case TokenType::DATE:
        return EU4Value{EU4Date{value}};
    default:
        throw std::runtime_error(
            "Syntax error (package): unexpected token of type " + std::to_string(static_cast<int>(type)) +
            " with value '" + value + "'");
    }
}

Tokenizer::Tokenizer(std::string path) : path{path}, reader(path) {};

Token Tokenizer::getNextToken()
{
    if (peekedToken.has_value()) // if the previous has a value
    {
        Token returningToken = peekedToken.value(); // we copy it
        peekedToken.reset();                        // we reset the optional member
        return returningToken;                      // we return the copy
    }
    std::string tokenData{}; // we build the token here (might change later for optimization)
    int dot_counter{};       // dot counter per token (helps detecting the tokentype)
    while (true)
    {
        int next_character;
        if (reader.peek() != -1)
        {
            next_character = reader.getNextCharacter();
        }
        else
        {
            next_character = -1;
        }
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
                reader.getNextCharacter(); // if it's an unquote we skip also get it but don't push it (we have a general [unquoted] STRING token)
            }
            else
            {
                throw std::runtime_error("Unexpected termination on quoted string"); // if it's an EOF, we can't make up data so we throw an exception
            }
            return Token(tokenData, TokenType::STRING);
        case EOF: // if it's the end  of the file
            if (!tokenData.empty())
            {
                return classifyToken(tokenData, dot_counter);
            }
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
    if (data == "---")
    {
        return Token(data, TokenType::STRING);
    }
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
    Token peeked{getNextToken()}; // we get the next
    peekedToken = peeked;         // save it as previous
    return peeked;                // return it
}
