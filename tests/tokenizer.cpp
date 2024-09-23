#include <iostream>
#include <tuple>
#include <cassert>
#include <algorithm>

#include "string/tokenizer.h"

template<typename C>
int
count(const C& c)
{
    return std::distance(c.begin(), c.end());
}

void
test_keep_empty_tokenizer()
{

    // clang-format off
    std::tuple<const char*, int> tuples[] = { 
        {"",              1},
        {",",             2},
        {",|",            3},
        {"Ala,ma,kota",   3},
        {",Ala,ma,kota",  4},
        {",Ala,ma,kota|", 5}
    };
    // clang-format on

    using tokenizer = O3::utils::string::tokenizer;

    std::cout << "Tokenizing string view, keeping empty tokens." << std::endl;
    for (const auto& tup : tuples) {
        std::cout << '[' << std::get<0>(tup) << ']' << std::endl;
        for (const auto& tok : tokenizer(std::string_view(std::get<0>(tup)), ",|", false)) {
            std::cout << '<' << tok << '>';
        }
        std::cout << std::endl;
    }

    // Count tokens
    std::cout << "Counting tokens" << std::endl;
    for (const auto& t : tuples) {
        auto  n = count(tokenizer(std::string_view(std::get<0>(t)), ",|", false));
        std::cout << '[' << std::get<0>(t) << ']' << " -> " << '(' << n << ')' << std::endl;
        assert(n == std::get<1>(t));
    }
}

void
test_skip_empty_tokenizer()
{

    // clang-format off
    std::tuple<const char*, int> tuples[] = { 
        {"",              0},
        {",",             0},
        {",|",            0},
        {"Ala,ma,kota",   3},
        {",Ala,ma,kota",  3},
        {",Ala,ma,kota|", 3}
    };
    // clang-format on

    using tokenizer = O3::utils::string::tokenizer;

    std::cout << "Tokenizing string view, skipping empty tokens." << std::endl;
    for (const auto& tup : tuples) {
        std::cout << '[' << std::get<0>(tup) << ']' << std::endl;
        for (const auto& tok : tokenizer(std::string_view(std::get<0>(tup)), ",|", true)) {
            std::cout << '<' << tok << '>';
        }
        std::cout << std::endl;
    }

    // Count tokens
    std::cout << "Counting tokens" << std::endl;
    for (const auto& t : tuples) {
        auto n = count(tokenizer(std::string_view(std::get<0>(t)), ",|", true));
        std::cout << '[' << std::get<0>(t) << ']' << " -> " << '(' << n << ')' << std::endl;
        assert(n == std::get<1>(t));
    }
}

int
main(int argc, char* argv[])
{
    test_keep_empty_tokenizer();
    test_skip_empty_tokenizer();

    std::cout << "All basic tests passed." << std::endl;

    return 0;
}
