#include <matrix.h>
#include <constants.h>
#include <vector>
#include <assert.h>
#include <tuple.h>

Matrix::Matrix(int _size){
    size = _size;
    elements = std::vector<float>(size*size, 0);
    for (int i=0; i<size; i++){
        elements[matrix_flatten(size, i, i)] = 1;
    }
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

Matrix transpose(Matrix& m){
    std::vector<float> result(m.size*m.size, 0);
    for (int i=0; i<m.size; i++){
        for (int j=0; j<m.size; j++){
            result[matrix_flatten(m.size, i, j)] = m.elements[matrix_flatten(m.size, j, i)];
        }
    }
    return Matrix(m.size, result);
}

float determinant(Matrix& m){
    if (m.size == 2){
        return m.elements[matrix_flatten(2, 0, 0)] *  m.elements[matrix_flatten(2, 1, 1)] - 
               m.elements[matrix_flatten(2, 1, 0)] *  m.elements[matrix_flatten(2, 0, 1)];
    }
    else {
        int result = 0;
        for (int j=0; j<m.size; j++){
            result += m.elements[matrix_flatten(m.size, 0, j)] * cofactor(m, 0, j);
        }
        return result;
    }
}

Matrix submatrix(Matrix& m, int x, int y){
    if (m.size == 1){
        return NULL;
    }
    std::vector<float> result((m.size-1)*(m.size-1), 0);
    int x_counter = 0;
    int y_counter = 0;
    for (int i=0; i<m.size; i++){
        if (i == x){
            continue;
        }
        for (int j=0; j<m.size; j++){
            if (j == y){
                continue;
            }

            result[matrix_flatten(m.size-1, x_counter, y_counter)] = m.elements[matrix_flatten(m.size, i, j)];

            y_counter += 1;
        }
        y_counter = 0;
        x_counter += 1;
    }
    return Matrix(m.size-1, result);
}

float minor(Matrix& m, int x, int y){
    if (m.size == 1){
        return NULL;
    }
    return determinant(submatrix(m, x, y));
}

float cofactor(Matrix& m, int x, int y){
    if (m.size == 1){
        return NULL;
    }
    int res = minor(m, x, y);
    if ((x + y) % 2 == 0){
        return res;
    }
    else {
        return -res;
    }
}

bool invertible(Matrix& m){
    return !float_equal(determinant(m), 0);
}

Matrix inverse(Matrix& m){
    assert(invertible(m));
    std::vector<float> result(m.size*m.size, 0);
    for (int row=0; row<m.size; row++){
        for (int col=0; col<m.size; col++){
            result[matrix_flatten(m.size, row, col)] = cofactor(m, col, row) / determinant(m);
        }
    }
    return Matrix(m.size, result);
}


bool operator==(const Matrix& lhs, const Matrix& rhs){
    if (lhs.size != rhs.size){
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

    float product = 0;
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