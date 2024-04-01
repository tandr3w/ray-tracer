#include <matrix.h>
#include <constants.h>
#include <vector>
#include <assert.h>
#include <tuple.h>

Matrix::Matrix(int _size){
    size = _size;
    elements = std::vector<float>(size*size, 0);
}

Matrix::Matrix(int _size, std::vector<float> init){
    size = _size;
    elements = init;
}

float Matrix::get(int x, int y) const{
    return elements[matrix_flatten(size, x, y)];
}

void Matrix::set(int x, int y, float val){
    elements[matrix_flatten(size, x, y)] = val;
}

int matrix_flatten(int size, int x, int y){
    return x*size + y;
}

bool operator==(const Matrix& lhs, const Matrix& rhs){
    if (lhs.size != rhs.size || lhs.size != rhs.size){
        return false;
    }
    for (int i=0; i<lhs.size; i++){
        for (int j=0; j<lhs.size; j++){
            if (!float_equal(lhs.get(i, j), rhs.get(i, j))){
                return false;
            }
        }
    }
    return true;
}

// Matrix operator+(const Matrix& lhs, const Matrix& rhs){

// }

// Matrix operator-(const Matrix& lhs, const Matrix& rhs){

// }

// Matrix operator-(const Matrix& t){

// }

Matrix operator*(const Matrix& lhs, const Matrix& rhs){
    assert(lhs.size == rhs.size);
    std::vector<float> productMatrix(lhs.size*lhs.size, 0);

    int product = 0;
    for (int row=0; row<lhs.size; row++){
        for (int col=0; col<lhs.size; col++){
            for (int i=0; i<lhs.size; i++){
                product += lhs.elements[matrix_flatten(lhs.size, row, i)] * rhs.elements[matrix_flatten(rhs.size, i, col)];
            }
            productMatrix[matrix_flatten(lhs.size, row, col)] = product;
            product = 0;
        }
    }
    Matrix result = Matrix(lhs.size, productMatrix);
    return result;
}

Tuple operator*(const Matrix& lhs, const Tuple& rhs){
    assert(lhs.size == 4);
    int product = 0;
    Tuple result = Tuple(0, 0, 0, 0);
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            product += lhs.elements[matrix_flatten(lhs.size, i, j)] * rhs.getByIndex(j);
        }
        result.setByIndex(i, product);
        product = 0;
    }
    return result;
}

// Matrix operator/(const Matrix& lhs, const float scale){

// }