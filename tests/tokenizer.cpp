#include <iostream>
#include <tuple>
#include <cassert>
#include <algorithm>

#include "string/tokenizer.h"

template<typename C>
std::pair<int, int>
count(const C& c)
{
    return { std::distance(c.begin(), c.end()),
             std::count_if(c.begin(), c.end(), [](const auto& t) { return !t.empty(); }) };
}

void
test_tokenizer()
{

    // clang-format off
    std::tuple<const char*, int, int> tuples[] = { 
        {"",              1, 0},
        {",",             2, 0},
        {",,",            3, 0},
        {"Ala,ma,kota",   3, 3},
        {",Ala,ma,kota",  4, 3},
        {",Ala,ma,kota,", 5, 3}
    };
    // clang-format on

    using tokenizer = O3::utils::string::tokenizer;

    // Explicit conversion from const char* to string view
    std::cout << "Tokenizing string view" << std::endl;
    for (const auto& tup : tuples) {
        std::cout << '[' << std::get<0>(tup) << ']' << std::endl;
        for (const auto& tok : tokenizer(std::string_view(std::get<0>(tup)), ',')) {
            std::cout << '<' << tok << '>';
        }
        std::cout << std::endl;
    }

    // Explicit conversion from const char* to string view
    std::cout << "Tokenizing string" << std::endl;
    for (const auto& tup : tuples) {
        std::cout << '[' << std::get<0>(tup) << ']' << std::endl;
        for (const auto& tok : tokenizer(std::string(std::get<0>(tup)), ',')) {
            std::cout << '<' << tok << '>';
        }
        std::cout << std::endl;
    }

    // Count tokens
    std::cout << "Counting tokens" << std::endl;
    for (const auto& t : tuples) {
        auto [a, n] = count(tokenizer(std::string_view(std::get<0>(t)), ','));
        std::cout << '[' << std::get<0>(t) << ']' << " -> " << '(' << a << ' ' << n << ')' << std::endl;
        assert(a == std::get<1>(t) && n == std::get<2>(t));
    }
}

int
main(int argc, char* argv[])
{
    test_tokenizer();

    std::cout << "All basic tests passed." << std::endl;

    return 0;
}
