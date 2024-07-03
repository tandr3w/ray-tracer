#ifndef H_MATRIX
#define H_MATRIX

#include <vector>
#include <string>
#include <tuple.h>

class Matrix {
    public:
        Matrix(int _size);
        Matrix(int _size, std::vector<float> init);
        int size;
        float get(int x, int y) const;
        void set(int x, int y, float val);
        std::vector<float> elements;
};

int matrix_flatten(int height, int x, int y);

bool operator==(const Matrix& lhs, const Matrix& rhs);

Matrix transpose(Matrix& m);

float determinant(Matrix& m);

Matrix submatrix(Matrix& m, int x, int y);

float minor(Matrix& m, int x, int y);

float cofactor(Matrix& m, int x, int y);

bool invertible(Matrix& m);

Matrix inverse(Matrix& m);

Matrix translation(float x, float y, float z);
Matrix scaling(float x, float y, float z); 

Matrix rotation_x(float radians); 
Matrix rotation_y(float radians); 
Matrix rotation_z(float radians);  

Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);  


Matrix operator*(const Matrix& lhs, const Matrix& rhs);
Tuple operator*(const Matrix& lhs, const Tuple& rhs);

#endif