#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "singleton.hpp"
#include <doctest/doctest.h>

struct Demo
{
    int x = 0;
    int y = 0;
};

TEST_CASE("Hello, World!") { CHECK(1 == 1); }

TEST_CASE("Singleton")
{
    auto& s1 = Singleton<Demo>::instance();
    auto& s2 = Singleton<Demo>::instance();
    CHECK(&s1 == &s2);
}