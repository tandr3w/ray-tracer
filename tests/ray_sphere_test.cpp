#include <catch2/catch_test_macros.hpp>
#include "matrix.h"
#include "constants.h"
#include "tuple.h"
#include "ray.h"
#include <vector>
#include <cstdint>
#include <cmath>

TEST_CASE("Rays") {
    Tuple origin = Point(1, 2, 3);
    Tuple direction = Vector(4, 5, 6);
    Ray r = Ray(origin, direction);
    REQUIRE(r.origin == origin);
    REQUIRE(r.direction == direction);
}


TEST_CASE("Ray Position") {
    Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));
    REQUIRE(r.Position(0) == Point(2, 3, 4));
    REQUIRE(r.Position(1) == Point(3, 3, 4));
    REQUIRE(r.Position(-1) == Point(1, 3, 4));
    REQUIRE(r.Position(2.5) == Point(4.5, 3, 4));
}
