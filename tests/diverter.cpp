#include <iostream>
#include <fstream>
#include <cassert>

#include "iostreams/diverter.h"

void
test_diverter()
{
    using O3::utils::iostreams::diverter;

    std::cout << "Hello, world! No diversion.\n";

    {
        std::ofstream log("diverter.log");
        diverter      d(std::cout, log);
        std::cout << "Hello, world! With diversion.\n";
    }

    std::cout << "Hello, world! Again no diversion.\n";
}

int
main(int argc, char* argv[])
{
    test_diverter();

    std::cout << "All basic tests passed." << std::endl;

    return 0;
}
