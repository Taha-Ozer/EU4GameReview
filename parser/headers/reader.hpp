#ifndef READER_HPP
#define READER_HPP
#include <string>
#include <fstream>
#include <iostream>
#include "types.hpp"

// Reader class to read the file and "pass" it to the tokenizer
class Reader
{
public:
    Reader(std::string path);
    // The necessary methods to build tokens
    char getNextCharacter();
    int peek();
    void putback(char c);

private:
    // we save the file path as a string and also open the file
    std::ifstream savegame;
    std::string filePath;
    unsigned long long index{};
};

#endif