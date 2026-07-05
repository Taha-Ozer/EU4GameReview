#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>
#include <iostream>
#include <string>
#include "../headers/types.hpp"
#include "../headers/parser.hpp"

namespace py = pybind11; // namespace alias for ease of use

template <class... Ts>
struct switchType : Ts...
{
    using Ts::operator()...;
};

template <class... Ts>
switchType(Ts...) -> switchType<Ts...>;

py::object eu4ToPy(const EU4Value &val)
{
    return std::visit(switchType{[](long long arg)
                                 { return py::cast(arg); }, // if we have a long long pybind11 can handle it
                                 [](float arg)
                                 { return py::cast(arg); }, // idem float
                                 [](const std::string &arg)
                                 { return py::reinterpret_steal<py::object>(PyUnicode_DecodeLatin1(arg.c_str(), arg.size(), nullptr)); }, // idem string
                                 [](bool arg)
                                 { return py::cast(arg); }, // idem bool
                                 [](const EU4Date &arg)
                                 {
                                     // for a date we return a tuple (year, month, date)
                                     return py::object(py::make_tuple(arg.year, arg.month, arg.day));
                                 },
                                 [](const EU4Block &arg)
                                 {
                                     py::dict block; // init an empty dictionary (python)
                                     int size = arg.size();
                                     for (int i = 0; i < size; i++)
                                     {
                                         // we iterate through the whole EU4Block
                                         const std::string key{arg[i].first}; // get the first element of the pair as the key
                                         if (!block.contains(key.c_str()))
                                         {
                                             block[key.c_str()] = eu4ToPy(*arg[i].second); // if there is no instance we initialize it
                                         }
                                         else if (!py::isinstance<py::list>(block[key.c_str()])) // if there is an instance but it isnt a list
                                         {
                                             py::list valueList;                        // we make a new list
                                             valueList.append(block[key.c_str()]);      // we append the existing value in the dict
                                             valueList.append(eu4ToPy(*arg[i].second)); // we append the second value
                                             block[key.c_str()] = valueList;            // we overwrite the dict value
                                         }
                                         else if (py::isinstance<py::list>(block[key.c_str()])) // if there is an instance and it's a list
                                         {
                                             py::list valueList = block[key.c_str()];   // we take the existing list from the dict
                                             valueList.append(eu4ToPy(*arg[i].second)); // we append the new value to it
                                             block[key.c_str()] = valueList;            // we overwrite the dict value
                                         }
                                     }
                                     return py::object(block); // we return the dictionary
                                 },
                                 [](const EU4List &arg)
                                 {
                                     py::list list; // init an empty list (python)
                                     int size = arg.size();
                                     for (int i = 0; i < size; i++)
                                     {
                                         // we iterate through the whole list
                                         list.append(eu4ToPy(*arg[i])); // and add it to the list
                                         // again we have to call recursively for the eu4ToPy() function as it can hold EU4Block and EU4List
                                     }
                                     return py::object(list);
                                 }},
                      val.data);
}

PYBIND11_MODULE(eu4tools, m)
{
    m.doc() = "A module for EU4 Save Game parsing in Python (Written in C++). By Taha";
    m.def("parse", [](const std::string &path)
          { Parser p{path}; return eu4ToPy(EU4Value{std::move(p.parseFile())}); });
}