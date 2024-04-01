#include <catch2/catch_test_macros.hpp>
#include "color.h"
#include "constants.h"

TEST_CASE("Color") {
    Color c = Color(-0.5, 0.4, 1.7);
    REQUIRE(float_equal(c.red, -0.5));
    REQUIRE(float_equal(c.green, 0.4));
    REQUIRE(float_equal(c.blue, 1.7));
}

TEST_CASE("Adding Colors") {
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    REQUIRE(c1 + c2 == Color(1.6, 0.7, 1.0));
}

TEST_CASE("Subtracting Colors") {
    Color c1 = Color(0.9, 0.6, 0.75);
    Color c2 = Color(0.7, 0.1, 0.25);
    REQUIRE(c1 - c2 == Color(0.2, 0.5, 0.5));
}

TEST_CASE("Color x Scalar") {
    Color c1 = Color(0.2, 0.3, 0.4);
    REQUIRE(c1 * 2 == Color(0.4, 0.6, 0.8));
}

TEST_CASE("Multiplying Colors") {
    Color c1 = Color(1, 0.2, 0.4);
    Color c2 = Color(0.9, 1, 0.1);
    REQUIRE(c1 * c2 == Color(0.9, 0.2, 0.04));
}
