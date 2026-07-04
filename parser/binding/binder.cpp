#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <variant>
#include <iostream>
#include <string>
#include "../headers/types.hpp"

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
                                 { return py::cast(arg); }, // idem string
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
                                         const std::string key{arg[i].first};          // get the first element of the pair as the key
                                         block[key.c_str()] = eu4ToPy(*arg[i].second); // and the second element as the value
                                         // though we have to recursively call eu4ToPy() because EU4Block can hold EU4Blocks and EU4Lists
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
