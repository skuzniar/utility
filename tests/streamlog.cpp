#include <iostream>
#include <numeric>
#include <vector>
#include <cassert>

#include "streamlog/log.h"

using namespace O3::utils::streamlog;

void
test_streamlog(log::threshold t)
{

    log::set(std::cout, t);

    const auto* const n = log::name(t);

    std::cout << "At threshold " << n << ": [" << "Unrestricted output" << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::debug("Debug output") << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::info("Info output") << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::warn("Warn output") << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::error("Error output") << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::fatal("Fatal output") << ']' << std::endl;
}
void
test_streamlog()
{
    test_streamlog(log::threshold::debug);
    test_streamlog(log::threshold::info);
    test_streamlog(log::threshold::warn);
    test_streamlog(log::threshold::error);
    test_streamlog(log::threshold::fatal);
}

void
test_colors()
{
    int ten = 10;

    std::cout << "    Red literal '10'" << ' ' << log::red(10)     << ' ' << "lvalue '10'" << ' ' << log::red(ten)     << std::endl;
    std::cout << "  Green literal '10'" << ' ' << log::green(10)   << ' ' << "lvalue '10'" << ' ' << log::green(ten)   << std::endl;
    std::cout << " Yellow literal '10'" << ' ' << log::yellow(10)  << ' ' << "lvalue '10'" << ' ' << log::yellow(ten)  << std::endl;
    std::cout << "   Blue literal '10'" << ' ' << log::blue(10)    << ' ' << "lvalue '10'" << ' ' << log::blue(ten)    << std::endl;
    std::cout << "Magenta literal '10'" << ' ' << log::magenta(10) << ' ' << "lvalue '10'" << ' ' << log::magenta(ten) << std::endl;
    std::cout << "   Cyan literal '10'" << ' ' << log::cyan(10)    << ' ' << "lvalue '10'" << ' ' << log::cyan(ten)    << std::endl;
    std::cout << "  White literal '10'" << ' ' << log::white(10)   << ' ' << "lvalue '10'" << ' ' << log::white(ten)   << std::endl;
}

int
main(int argc, char* argv[])
{
    test_streamlog();
    test_colors();

    std::cout << "All basic tests passed." << std::endl;

    return 0;
}
