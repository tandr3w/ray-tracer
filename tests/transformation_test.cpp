#include <catch2/catch_test_macros.hpp>
#include "matrix.h"
#include "tuple.h"
#include "constants.h"
#include <vector>
#include <cstdint>
#include <cmath>

TEST_CASE("Matrix Transformation") {
  Matrix transform = translation(5, -3, 2);
  Tuple p = Point(-3, 4, 5);
  REQUIRE(transform * p == Point(2, 1, 7));
  Matrix inv = inverse(transform);
  REQUIRE(inv * p == Point(-8, 7, 3));
}

TEST_CASE("Translation Does Not Affect Vectors"){
  Matrix transform = translation(5, -3, 2);
  Tuple v = Vector(-3, 4, 5);
  REQUIRE(transform * v == v);
}