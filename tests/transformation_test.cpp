#include <catch2/catch_test_macros.hpp>
#include "matrix.h"
#include "tuple.h"
#include "constants.h"
#include <vector>
#include <cstdint>
#include <cmath>

TEST_CASE("Translation") {
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

TEST_CASE("Scaling") {
  Matrix transform = scaling(2, 3, 4);
  Tuple p = Point(-4, 6, 8);
  REQUIRE(transform * p == Point(-8, 18, 32));
  Tuple v = Vector(-4, 6, 8);
  REQUIRE(transform * v == Vector(-8, 18, 32));

  Matrix inv = inverse(transform);
  REQUIRE(inv * v == Vector(-2, 2, 2));
}

TEST_CASE("Reflection"){
  Matrix transform = scaling(-1, 1, 1);
  Tuple p = Point(2, 3, 4);
  REQUIRE(transform * p == Point(-2, 3, 4));
}

TEST_CASE("X Rotation"){
  Matrix half_quarter = rotation_x(PI/4);
  Matrix full_quarter = rotation_x(PI/2);
  Tuple p = Point(0, 1, 0);
  REQUIRE(half_quarter * p == Point(0, sqrt(2)/2, sqrt(2)/2));
  REQUIRE(full_quarter * p == Point(0, 0, 1));

  Matrix inv = inverse(half_quarter);
  REQUIRE(inv * p == Point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST_CASE("Y Rotation"){
  Matrix half_quarter = rotation_y(PI/4);
  Matrix full_quarter = rotation_y(PI/2);
  Tuple p = Point(0, 0, 1);
  REQUIRE(half_quarter * p == Point(sqrt(2)/2, 0, sqrt(2)/2));
  REQUIRE(full_quarter * p == Point(1, 0, 0));
}

TEST_CASE("Z Rotation"){
  Matrix half_quarter = rotation_z(PI/4);
  Matrix full_quarter = rotation_z(PI/2);
  Tuple p = Point(0, 1, 0);
  REQUIRE(half_quarter * p == Point(-sqrt(2)/2, sqrt(2)/2, 0));
  REQUIRE(full_quarter * p == Point(-1, 0, 0));
}

TEST_CASE("Shearing"){
  Matrix transform = shearing(1, 0, 0, 0, 0, 0);
  Tuple p = Point(2, 3, 4);
  REQUIRE(transform * p == Point(5, 3, 4));

  transform = shearing(0, 1, 0, 0, 0, 0);
  REQUIRE(transform * p == Point(6, 3, 4));

  transform = shearing(0, 0, 1, 0, 0, 0);
  REQUIRE(transform * p == Point(2, 5, 4));

  transform = shearing(0, 0, 0, 1, 0, 0);
  REQUIRE(transform * p == Point(2, 7, 4));

  transform = shearing(0, 0, 0, 0, 1, 0);
  REQUIRE(transform * p == Point(2, 3, 6));

  transform = shearing(0, 0, 0, 0, 0, 1);
  REQUIRE(transform * p == Point(2, 3, 7));
}

TEST_CASE("Chaining Transformations"){
  Tuple p = Point(1, 0, 1);
  Matrix A = rotation_x(PI/2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);

  Tuple p1 = A * p;
  Tuple p2 = B * p1;
  Tuple p3 = C * p2;

  REQUIRE(p1 == Point(1, -1, 0));
  REQUIRE(p2 == Point(5, -5, 0));
  REQUIRE(p3 == Point(15, 0, 7));

  REQUIRE((C * B * A) * p == Point(15, 0, 7));
}