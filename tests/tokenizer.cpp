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
    using O3::utils::string::tokenizer;

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

    for (const auto& t : tuples) {
        auto [a, n] = count(tokenizer(std::get<0>(t), ','));
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
