#include <iostream>
#include "parser/headers/parser.hpp"
#include "parser/headers/protoypes.hpp"
#include "parser/headers/reader.hpp"
#include "parser/headers/tokenizer.hpp"
#include "parser/headers/types.hpp"

int main()
{
    std::string filepath{"C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"};
    Parser p{filepath};
    p.parseFile();

    std::cout << "Works!";

    return 0;
}