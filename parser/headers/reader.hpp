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

private:
    std::ifstream savegame;
    std::string filePath;
    unsigned long long index{};
};

#endif