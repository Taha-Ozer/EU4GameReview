#include "../headers/tokenizer.hpp"

Tokenizer::Tokenizer(std::string path) : path{path}, reader(path) {};

Token Tokenizer::getNextToken()
{
}