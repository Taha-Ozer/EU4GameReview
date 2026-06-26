#include "../headers/types.hpp"
#include <algorithm>
#include <stdexcept>

// construct out of a string
EU4Date::EU4Date(const std::string &date)
{
    int length{date.length()};
    std::string accumulator{}; // we accumulate the date-data in this
    int dotCounter{};          // we keep amount of dots
    for (int letterIdx = 0; letterIdx < length; letterIdx++)
    {
        // if it's not a dot
        if (date[letterIdx] != '.')
        {
            // we add it to the string
            accumulator.push_back(date[letterIdx]);
        }
        // if the length isn't 0 and we come across a dot
        else if (accumulator.length() != 0)
        {
            // we check the value of the dotcounter
            switch (dotCounter)
            {
            case 0:
                // if there aren't dots yet. It's the year
                dotCounter++;
                year = std::stoi(accumulator);
                accumulator.clear();
                break;
            // else it's the day
            case 1:
                dotCounter++;
                month = std::stoi(accumulator);
                accumulator.clear();
                break;
            default:
                throw std::runtime_error("You can't have 3 dots in a DATE token");
            }
        }
    }
    // there is no trailing dot so we add the content of the accumulator into day and clear it
    day = std::stoi(accumulator);
    accumulator.clear();
}