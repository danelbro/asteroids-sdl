#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <numeric>
#include <vector>

int main()
try
{
    std::string name{ "fps.log" };
    std::ifstream fpsLog{ name };
    if (!fpsLog)
        throw std::runtime_error("Can't open input file " + name);
    std::vector<double> values{ };
    double value{ };
    while (fpsLog >> value) {
        values.push_back(value);
    }

    auto minmax{ std::minmax_element(values.begin(), values.end()) };

    double average{
        static_cast<double>(std::accumulate(values.begin(), values.end(), 0))
        / values.size() };
    auto lowElem{ std::distance(values.begin(), minmax.first) };
    auto highElem{ std::distance(values.begin(), minmax.second) };
    double lowest{ values.at(static_cast<unsigned long>(lowElem)) };
    double highest{ values.at(static_cast<unsigned long>(highElem))} ;

    std::cout << "Total frames: " << values.size() << '\n'
              << "Average framerate: " << average << '\n'
              << "Max: " << highest << " (element "
              << std::distance(values.begin(), minmax.second) << ")\n"
              << "Min: " << lowest << " (element "
              << std::distance(values.begin(), minmax.first) << ")\n";

    return 0;
}
catch (std::exception &e)
{
    std::cerr << "Exception: " << e.what();
}
catch (...)
{
    std::cerr << "Unknown exception\n";
}
