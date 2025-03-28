#include <fmt/core.h>
#include <iostream>

extern const char* COREVERSION;
extern const char* BUILDDATE;
extern const char* COPYRIGHT;

int main()
{
    std::cout << "Hello, World!" << std::endl;
    fmt::print("core version: {}\n", COREVERSION);
    fmt::print("build data: {}\n", BUILDDATE);
    fmt::println("{}", COPYRIGHT);
    return 0;
}