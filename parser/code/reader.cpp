#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "../headers/reader.hpp"

Reader::Reader(std::string path) : filePath{path}, savegame(path)
{
    if (!savegame.is_open())
    {
        throw std::runtime_error("couldn't open file");
    }
};

char Reader::getNextCharacter()
{
    char current_character;
    if (savegame.get(current_character))
    {
        return current_character;
    }
    throw std::runtime_error("File is no more");
}

int Reader::peek()
{
    return savegame.peek();
}