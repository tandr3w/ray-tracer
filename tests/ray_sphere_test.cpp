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
