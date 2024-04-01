#include <catch2/catch_test_macros.hpp>
#include "matrix.h"
#include "constants.h"
#include <vector>
#include <cstdint>
#include <cmath>

TEST_CASE("Matrix") {
    Matrix M = Matrix(4, std::vector<float>({1, 2, 3, 4,
                                                5.5, 6.5, 7.5, 8.5,
                                                9, 10, 11, 12,
                                                13.5, 14.5, 15.5, 16.5
                                                }));
    REQUIRE(float_equal(M.get(0,0), 1));
    REQUIRE(float_equal(M.get(0,3), 4));
    REQUIRE(float_equal(M.get(1,0), 5.5));
    REQUIRE(float_equal(M.get(1,2), 7.5));
    REQUIRE(float_equal(M.get(2,2), 11));
    REQUIRE(float_equal(M.get(3,0), 13.5));
    REQUIRE(float_equal(M.get(3,2), 15.5));

    Matrix M2 = Matrix(2, std::vector<float>({-3, 5, 1, -2}));
    REQUIRE(float_equal(M2.get(0,0), -3));
    REQUIRE(float_equal(M2.get(0,1), 5));
    REQUIRE(float_equal(M2.get(1,0), 1));
    REQUIRE(float_equal(M2.get(1,1), -2));

    Matrix M3 = Matrix(3, std::vector<float>({-3, 5, 0, 1, -2, -7, 0, 1, 1}));
    REQUIRE(float_equal(M3.get(0,0), -3));
    REQUIRE(float_equal(M3.get(1,1), -2));
    REQUIRE(float_equal(M3.get(2,2), 1));
}

TEST_CASE("Matrix Equality") {
    Matrix M1 = Matrix(4, std::vector<float>({1, 2, 3, 4,
                                                 5, 6, 7, 8,
                                                 9, 8, 7, 6,
                                                 5, 4, 3, 2}));
    Matrix M2 = Matrix(4, std::vector<float>({1, 2, 3, 4,
                                                 5, 6, 7, 8,
                                                 9, 8, 7, 6,
                                                 5, 4, 3, 2}));
    Matrix M3 = Matrix(4, std::vector<float>({2, 3, 4, 5,
                                                 6, 7, 8, 9,
                                                 8, 7, 6, 5,
                                                 4, 3, 2, 1}));
    REQUIRE(M1 == M2);
    REQUIRE((M1 == M3) == false);
}

TEST_CASE("Matrix Multiplication") {
    Matrix M1 = Matrix(4, std::vector<float>({1, 2, 3, 4,
                                                 5, 6, 7, 8,
                                                 9, 8, 7, 6,
                                                 5, 4, 3, 2}));
    Matrix M2 = Matrix(4, std::vector<float>({-2, 1, 2, 3,
                                                 3, 2, 1, -1,
                                                 4, 3, 6, 5,
                                                 1, 2, 7, 8}));
    REQUIRE(M1*M2 == Matrix(4, std::vector<float>({20, 22, 50, 48,
                                                 44, 54, 114, 108,
                                                 40, 58, 110, 102,
                                                 16, 26, 46, 42})));
}

TEST_CASE("Matrix & Tuple Multiplication") {
    Matrix M1 = Matrix(4, std::vector<float>({1, 2, 3, 4,
                                              2, 4, 4, 2,
                                              8, 6, 4, 1,
                                              0, 0, 0, 1}));
    Tuple B = Tuple(1, 2, 3, 1);
    REQUIRE(M1*B == Tuple(18, 24, 33, 1));
}



