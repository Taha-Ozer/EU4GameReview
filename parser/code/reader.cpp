#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include "../headers/reader.hpp"

// reader source file

// Constructor
Reader::Reader(std::string path) : filePath{path}, savegame(path)
{
    if (!savegame.is_open())
    {
        throw std::runtime_error("couldn't open file"); // basic check if file could be opened or not
    }
};

char Reader::getNextCharacter()
{
    char current_character;
    if (savegame.get(current_character))
    {
        return current_character; // we get the next character from the istream and return it
    }
    throw std::runtime_error("File is no more"); // if there isn't a new character we throw an exception that the file is done
}

int Reader::peek()
{
    return savegame.peek(); // this is used to peek at the next character. Handy for making quoted string tokens
}

void Reader::putback(char c)
{
    savegame.putback(c); // we use this to prevent token losses so we can put read characters (like braces) back to the istream.
}