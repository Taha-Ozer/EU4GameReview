#include <variant>
#include <memory>
#include <string>
#include <vector>

#ifndef TYPES_HPP
#define TYPES_HPP

struct EU4Value; // Forward declaration of the main struct.

using EU4Block = std::vector<std::pair<std::string, std::unique_ptr<EU4Value>>>; // EU4Block datatype for blocks { over many lines }.

using EU4List = std::vector<std::unique_ptr<EU4Value>>; // EU4List datatype for space separated lists: { HEY THIS IS AN EU4List }.

struct EU4Value
{
    std::variant<int, float, std::string, EU4Block, EU4List> data;
};

#endif