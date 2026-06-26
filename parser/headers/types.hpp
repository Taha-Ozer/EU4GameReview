#ifndef TYPES_HPP
#define TYPES_HPP

#include <variant>
#include <memory>
#include <string>
#include <vector>

struct EU4Value; // Forward declaration of the main struct.

using EU4Block = std::vector<std::pair<std::string, std::unique_ptr<EU4Value>>>; // EU4Block datatype for blocks { over many lines }.

using EU4List = std::vector<std::unique_ptr<EU4Value>>; // EU4List datatype for space separated lists: { HEY THIS IS AN EU4List }.

struct EU4Date
{
    // construct out of a string
    EU4Date(const std::string &date);
    bool operator==(const EU4Date &other) const;
    bool operator!=(const EU4Date &other) const;
    bool operator>(const EU4Date &other) const;
    bool operator<(const EU4Date &other) const;
    bool operator>=(const EU4Date &other) const;
    bool operator<=(const EU4Date &other) const;
    int day{};
    int month{};
    int year{};
};

struct EU4Value
{
    std::variant<int, float, bool, EU4Date, std::string, EU4Block, EU4List> data;
};

#endif