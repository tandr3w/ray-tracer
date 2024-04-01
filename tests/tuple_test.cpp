#include <catch2/catch_test_macros.hpp>
#include "tuple.h"
#include "constants.h"
#include <cstdint>
#include <cmath>

TEST_CASE("Tuple 1") {
    Tuple t(4.3, -4.2, 3.1, 1.0);
    REQUIRE(float_equal(t.x, 4.3f));
    REQUIRE(float_equal(t.y, -4.2f));
    REQUIRE(float_equal(t.z, 3.1f));
    REQUIRE(float_equal(t.w, 1.0f));
    REQUIRE(t.isPoint() == true);
    REQUIRE(t.isVector() == false);
}

TEST_CASE("Tuple 2") {
    Tuple t(4.3, -4.2, 3.1, 0.0);
    REQUIRE(float_equal(t.x, 4.3f));
    REQUIRE(float_equal(t.y, -4.2f));
    REQUIRE(float_equal(t.z, 3.1f));
    REQUIRE(float_equal(t.w, 0.0f));
    REQUIRE(t.isPoint() == false);
    REQUIRE(t.isVector() == true);
}

TEST_CASE("Point") {
    Tuple p = Point(4, -4, 3);
    REQUIRE(p == Tuple(4, -4, 3, 1.0));
}

TEST_CASE("Vector") {
    Tuple v = Vector(4, -4, 3);
    REQUIRE(v == Tuple(4, -4, 3, 0.0));
}

TEST_CASE("Tuple Addition") {
    Tuple a1 = Tuple(3, -2, 5, 1);
    Tuple a2 = Tuple(-2, 3, 1, 0);
    REQUIRE(a1 + a2 == Tuple(1, 1, 6, 1));
}

TEST_CASE("Tuple Subtraction") {
    Tuple p1 = Point(3, 2, 1);
    Tuple p2 = Point(5, 6, 7);
    REQUIRE(p1 - p2 == Vector(-2, -4, -6));

    Tuple p = Point(3, 2, 1);
    Tuple v = Vector(5, 6, 7);
    REQUIRE(p - v == Point(-2, -4, -6));
}

TEST_CASE("Tuple Negation") {
    Tuple zero = Tuple(0, 0, 0, 0);
    Tuple v = Vector(1, -2, 3);
    REQUIRE(zero - v == Vector(-1, 2, -3));
    Tuple a = Tuple(1, -2, 3, -4);
    REQUIRE(-a == Tuple(-1, 2, -3, 4));
}

TEST_CASE("Tuple Multiplication") {
    Tuple a = Tuple(1, -2, 3, -4);
    REQUIRE(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
}

TEST_CASE("Tuple Division") {
    Tuple a = Tuple(1, -2, 3, -4);
    REQUIRE(a / 2 == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Tuple Magnitude") {
    REQUIRE(float_equal(Magnitude(Vector(1, 0, 0)), 1));
    REQUIRE(float_equal(Magnitude(Vector(0, 1, 0)), 1));
    REQUIRE(float_equal(Magnitude(Vector(0, 0, 1)), 1));
    REQUIRE(float_equal(Magnitude(Vector(1, 2, 3)), sqrt(14)));
    REQUIRE(float_equal(Magnitude(Vector(-1, -2, -3)), sqrt(14)));
}

TEST_CASE("Tuple Normalization") {
    REQUIRE(Normalize(Vector(4, 0, 0)) == Vector(1, 0, 0));
    REQUIRE(Normalize(Vector(1, 2, 3)) == Vector(1/sqrt(14), 2/sqrt(14), 3/sqrt(14)));
    REQUIRE(float_equal(Magnitude(Normalize(Vector(1, 2, 3))), 1));
}

TEST_CASE("Dot Product") {
    REQUIRE(float_equal(dot(Vector(1, 2, 3), Vector(2, 3, 4)), 20));
}

TEST_CASE("Cross Product") {
    Tuple v1 = Vector(1, 2, 3);
    Tuple v2 = Vector(2, 3, 4);
    REQUIRE(cross(v1, v2) == Vector(-1, 2, -1));
    REQUIRE(cross(v2, v1) == Vector(1, -2, 1));
}

TEST_CASE("Get By Index") {
    Tuple v1 = Tuple(1, 2, 3, 1);
    REQUIRE(float_equal(v1.getByIndex(0), 1));
    REQUIRE(float_equal(v1.getByIndex(1), 2));
    REQUIRE(float_equal(v1.getByIndex(2), 3));
    REQUIRE(float_equal(v1.getByIndex(3), 1));
}

TEST_CASE("Set By Index") {
    Tuple v1 = Tuple(0, 0, 0, 0);
    v1.setByIndex(0, 1);
    v1.setByIndex(1, 2);
    v1.setByIndex(2, 3);
    v1.setByIndex(3, 4);
    REQUIRE(float_equal(v1.x, 1));
    REQUIRE(float_equal(v1.y, 2));
    REQUIRE(float_equal(v1.z, 3));
    REQUIRE(float_equal(v1.w, 4));
}
