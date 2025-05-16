#define CATCH_CONFIG_MAIN 
#include <catch2/catch_all.hpp>
#include "vector.h"

TEST_CASE("Vector constructors", "[vector]") {
    SECTION("Default constructor") {
        Vector<int> v;
        REQUIRE(v.size() == 0);
        REQUIRE(v.capacity() == 1);
        REQUIRE(v.empty());
    }
}