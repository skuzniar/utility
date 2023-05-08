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

    const auto n = log::name(t);

    std::cout << "At threshold " << n << ": [" << "Unrestricted output"      << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::debug("Debug output") << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::info("Info output")   << ']' << std::endl;
    std::cout << "At threshold " << n << ": [" << log::warn("Warn output")   << ']' << std::endl;
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

int
main(int argc, char* argv[])
{
    test_streamlog();

    std::cout << "All basic tests passed." << std::endl;

    return 0;
}
