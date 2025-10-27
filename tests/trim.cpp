#include <iostream>
#include <cassert>

#include "string/trim.h"

namespace {

void
test_ltrim()
{
    // clang-format off
    std::tuple<std::string, std::string> tuples[] = { 
        {"",              ""},
        {"X",             "X"},
        {" X",            "X"},
        {"  X",           "X"},
        {"\tX",           "X"},
        {"\t\tX",         "X"},
        {"\t X",          "X"},
        {" \tX",          "X"},
    };
    // clang-format on

    using O3::utils::string::ltrim;

    std::cout << "Left trimming." << std::endl;
    for (const auto& [src, res] : tuples) {
        assert(ltrim(src) == res);
    }
}

void
test_rtrim()
{
    // clang-format off
    std::tuple<std::string, std::string> tuples[] = { 
        {"",              ""},
        {"X",             "X"},
        {"X ",            "X"},
        {"X  ",           "X"},
        {"X\t",           "X"},
        {"X\t\t",         "X"},
        {"X\t ",          "X"},
        {"X \t",          "X"},
    };
    // clang-format on

    using O3::utils::string::rtrim;

    std::cout << "Right trimming." << std::endl;
    for (const auto& [src, res] : tuples) {
        assert(rtrim(src) == res);
    }
}

void
test_trim()
{
    // clang-format off
    std::tuple<std::string, std::string> tuples[] = { 
        {"",              ""},
        {"X",             "X"},
        {" X ",           "X"},
        {"  X  ",         "X"},
        {"\tX\t",         "X"},
        {"\t\tX\t\t",     "X"},
        {"\t X\t ",       "X"},
        {" \tX \t",       "X"},
    };
    // clang-format on

    using O3::utils::string::trim;

    std::cout << "Left and right trimming." << std::endl;
    for (const auto& [src, res] : tuples) {
        assert(trim(src) == res);
    }
}

void
test_starts_with()
{
    // clang-format off
    std::tuple<std::string, std::string, bool> tuples[] = { 
        {"",             "",     true},
        {"X",            "X",    true},
        {"X ",           "X",    true},
        {"  X  ",        "  X",  true},
        {"\tX\t",        "\tX",  true},
        {"\t\tX\t\t",    "\tX",  false},
        {"\t X\t ",      " X",   false},
        {" \tX \t",      " \tX", true},
    };
    // clang-format on

    using O3::utils::string::starts_with;

    std::cout << "Starts with testing." << std::endl;
    for (const auto& [src, pre, res] : tuples) {
        assert(starts_with(src, pre) == res);
    }
}

void
test_ends_with()
{
    // clang-format off
    std::tuple<std::string, std::string, bool> tuples[] = { 
        {"",             "",     true},
        {"X",            "X",    true},
        {" X",           "X",    true},
        {"  X  ",        "X  ",  true},
        {"\tX\t",        "X\t",  true},
        {"\t\tX\t\t",    "X\t",  false},
        {"\t X\t ",      "X ",   false},
        {" \tX \t",      "X \t", true},
    };
    // clang-format on

    using O3::utils::string::ends_with;

    std::cout << "Ends with testing." << std::endl;
    for (const auto& [src, pre, res] : tuples) {
        assert(ends_with(src, pre) == res);
    }
}

} // namespace

int
main()
{
    test_ltrim();
    test_rtrim();
    test_trim();

    test_starts_with();
    test_ends_with();

    std::cout << "All tests passed." << std::endl;

    return 0;
}
