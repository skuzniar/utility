#include <iostream>
#include <numeric>
#include <vector>
#include <cassert>

#include "iostreams/hexdump.h"

void
test_hexdump()
{
    using O3::utils::iostreams::hexdump;

    std::vector<unsigned char> v(256);

    std::iota(v.begin(), v.end(), 0);

    std::cout << "One line:\n[" << hexdump(v.data(), v.size()) << ']' << std::endl;

    std::cout << "Multi line:\n" << hexdump(v.data(), v.size(), 10) << std::endl;
}

int
main(int argc, char* argv[])
{
    test_hexdump();

    std::cout << "All basic tests passed." << std::endl;

    return 0;
}
