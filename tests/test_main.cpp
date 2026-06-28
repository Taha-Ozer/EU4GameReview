#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <string>

#include "../parser/headers/parser.hpp"
#include "../parser/headers/types.hpp"

// Helper function to create dummy save files for testing
void create_temp_file(const std::string &path, const std::string &content)
{
    std::ofstream out(path);
    out << content;
    out.close();
}

void test_date_parsing()
{
    std::cout << "Running Date Parsing Tests..." << std::endl;

    EU4Date d1("1444.11.11");
    assert(d1.year == 1444);
    assert(d1.month == 11);
    assert(d1.day == 11);

    EU4Date d2("1444.11.12");
    assert(d1 < d2);
    assert(d2 > d1);
    assert(d1 != d2);
    assert(d1 <= d2);
}

void test_parser_basic_key_values()
{
    std::cout << "Running Basic Key-Value Parsing Tests..." << std::endl;

    std::string path = "temp_test_basic.eu4";
    create_temp_file(path, "name = \"France\"\ncore = yes\nmanpower = 10.5\n");

    Parser p(path);
    EU4Block block = p.parseFile();

    assert(block.size() == 3);

    // Check String
    assert(block[0].first == "name");
    assert(std::get<std::string>(block[0].second->data) == "France");

    // Check Bool
    assert(block[1].first == "core");
    assert(std::get<bool>(block[1].second->data) == true);

    // Check Float
    assert(block[2].first == "manpower");
    assert(std::get<float>(block[2].second->data) == 10.5f);

    std::remove(path.c_str());
}

void test_parser_lists()
{
    std::cout << "Running List Parsing Tests..." << std::endl;

    std::string path = "temp_test_list.eu4";
    create_temp_file(path, "allies = { \"ENG\" \"SPA\" }");

    Parser p(path);
    EU4Block block = p.parseFile();

    assert(block.size() == 1);
    assert(block[0].first == "allies");

    // Extract the list
    const EU4List &list = std::get<EU4List>(block[0].second->data);
    assert(list.size() == 2);
    assert(std::get<std::string>(list[0]->data) == "ENG");
    assert(std::get<std::string>(list[1]->data) == "SPA");

    std::remove(path.c_str());
}

void test_parser_nested_blocks()
{
    std::cout << "Running Nested Block Parsing Tests..." << std::endl;

    std::string path = "temp_test_nested.eu4";
    create_temp_file(path, "stats = { development = 10 tax = 5 }");

    Parser p(path);
    EU4Block block = p.parseFile();

    assert(block.size() == 1);
    assert(block[0].first == "stats");

    // Extract the nested block
    const EU4Block &nested = std::get<EU4Block>(block[0].second->data);
    assert(nested.size() == 2);

    assert(nested[0].first == "development");
    assert(std::get<long long>(nested[0].second->data) == 10);

    assert(nested[1].first == "tax");
    assert(std::get<long long>(nested[1].second->data) == 5);

    std::remove(path.c_str());
}

int main()
{
    std::cout << "--- Starting EU4 Parser Test Suite ---" << std::endl;

    test_date_parsing();
    test_parser_basic_key_values();
    test_parser_lists();
    test_parser_nested_blocks();

    std::cout << "--- All tests passed successfully! ---" << std::endl;
    return 0;
}