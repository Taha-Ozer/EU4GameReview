#ifndef READER_HPP
#define READER_HPP
#include <string>
#include <fstream>
#include <iostream>
#include "types.hpp"

class Reader
{
public:
    Reader(std::string path);
    char getNextCharacter();
    int peek();
    void putback(char c);

private:
    std::ifstream savegame;
    std::string filePath;
    unsigned long long index{};
};

#endif