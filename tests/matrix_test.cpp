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

TEST_CASE("Identity Matrix"){
    Matrix M1 = Matrix(4, std::vector<float>({20, 22, 50, 48,
                                            44, 54, 114, 108,
                                            40, 58, 110, 102,
                                            16, 26, 46, 42}));
    Matrix identity = Matrix(4);
    REQUIRE(M1*identity == M1);
}

TEST_CASE("Transpose Matrix"){
    Matrix M1 = Matrix(4, std::vector<float>({0, 9, 3, 0,
                                              9, 8, 0, 8,
                                              1, 8, 5, 3, 
                                              0, 0, 5, 8}));
    Matrix M2 = Matrix(4, std::vector<float>({0, 9, 1, 0,
                                              9, 8, 8, 0,
                                              3, 0, 5, 5, 
                                              0, 8, 3, 8}));
    Matrix identity = Matrix(4);
    REQUIRE(transpose(M1) == M2);
    REQUIRE(transpose(identity) == identity);
}

TEST_CASE("Matrix Determinant"){
    Matrix A = Matrix(2, std::vector<float>({1, 5, -3, 2}));
    REQUIRE(float_equal(determinant(A), 17));
}

TEST_CASE("Submatrix"){
    Matrix A = Matrix(3, std::vector<float>({1, 5, 0, -3, 2, 7, 0, 6, -3}));
    REQUIRE(submatrix(A, 0, 2) == Matrix(2, std::vector<float>({-3, 2, 0, 6})));
}

TEST_CASE("Minor & Cofactor"){
    Matrix A = Matrix(3, std::vector<float>({3, 5, 0,
                                            2, -1, -7, 
                                            6, -1, 5}));
    Matrix B = submatrix(A, 1, 0);
    REQUIRE(float_equal(determinant(B), 25));                                  
    REQUIRE(float_equal(minor(A, 1, 0), 25));                                  
    REQUIRE(float_equal(minor(A, 0, 0), -12));                                  
    REQUIRE(float_equal(cofactor(A, 1, 0), -25));                                  
    REQUIRE(float_equal(cofactor(A, 0, 0), -12));                                  
}

TEST_CASE("Large Matrix Determinants"){
    Matrix A = Matrix(3, std::vector<float>({1, 2, 6, -5, 8, -4, 2, 6, 4}));
    Matrix B = Matrix(4, std::vector<float>({-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9}));
    REQUIRE(float_equal(cofactor(A, 0, 0), 56));
    REQUIRE(float_equal(cofactor(A, 0, 1), 12));
    REQUIRE(float_equal(cofactor(A, 0, 2), -46));
    REQUIRE(float_equal(determinant(A), -196));
    REQUIRE(float_equal(cofactor(B, 0, 0), 690));
    REQUIRE(float_equal(cofactor(B, 0, 1), 447));
    REQUIRE(float_equal(cofactor(B, 0, 2), 210));
    REQUIRE(float_equal(cofactor(B, 0, 3), 51));
    REQUIRE(float_equal(determinant(B), -4071));
}

TEST_CASE("Testing for Invertibility"){
    Matrix A = Matrix(4, std::vector<float>({6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6}));
    Matrix B = Matrix(4, std::vector<float>({-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0}));
    REQUIRE(float_equal(determinant(A), -2120));
    REQUIRE(invertible(A) == true);
    REQUIRE(float_equal(determinant(B), 0));
    REQUIRE(invertible(B) == false);
}

TEST_CASE("Inverse Matrix"){
    Matrix A = Matrix(4, std::vector<float>({-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4}));
    Matrix B = inverse(A);
    REQUIRE(float_equal(determinant(A), 532));
    REQUIRE(float_equal(cofactor(A, 2, 3), -160));
    REQUIRE(float_equal(B.elements[matrix_flatten(B.size, 3, 2)], -160.0f/532.0f));
    REQUIRE(float_equal(cofactor(A, 3, 2), 105));
    REQUIRE(float_equal(B.elements[matrix_flatten(B.size, 2, 3)], 105.0f/532.0f));
    REQUIRE(B == Matrix(4, std::vector<float>({0.21805, 0.45113, 0.24060, -0.04511,
                                               -0.80827, -1.45677, -0.44361, 0.52068,
                                               -0.07895, -0.22368, -0.05263, 0.19737,
                                               -0.52256, -0.81391, -0.30075, 0.30639})));

    Matrix C = Matrix(4, std::vector<float>({
      8, -5, 9, 2, 
      7, 5, 6, 1, 
      -6, 0, 9, 6, 
      -3, 0, -9, -4,    
    }));

    REQUIRE(inverse(C) == Matrix(4, std::vector<float>({
      -0.15385, -0.15385, -0.28205, -0.53846, 
      -0.07692, 0.12308, 0.02564, 0.03077, 
      0.35897, 0.35897, 0.43590, 0.92308, 
      -0.69231, -0.69231, -0.76923, -1.92308, 
    })));     

    Matrix D = Matrix(4, std::vector<float>({
      9, 3, 0, 9, 
      -5, -2, -6, -3, 
      -4, 9, 6, 4, 
      -7, 6, 6, 2, 
    }));

    REQUIRE(inverse(D) == Matrix(4, std::vector<float>({
      -0.04074, -0.07778, 0.14444, -0.22222, 
      -0.07778, 0.03333, 0.36667, -0.33333, 
      -0.02901, -0.14630, -0.10926, 0.12963, 
      0.17778, 0.06667, -0.26667, 0.33333, 
    })));              

    Matrix E = Matrix(4, std::vector<float>({
      3, -9, 7, 3,
      3, -8, 2, -9,
      -4, 4, 4, 1,
      -6, 5, -1, 1,
    }));

    Matrix F = Matrix(4, std::vector<float>({
      8, 2, 2, 2,
      3, -1, 7, 0,
      7, 0, 5, 4,
      6, -2, 0, 5,
    }));               

    REQUIRE(E == ((E*F) * inverse(F))); 
}
