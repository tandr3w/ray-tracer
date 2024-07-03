#include <iostream>
#include "tuple.h"

// TODO:
// Convert vectors to dynamically allocated arrays
// Split matrix functions into 4x4, 3x3, 2x2, etc. for more code clarity
// Turn things that should be constants into constants
// Make the matrix elements list a private attribute, and stop using matrix_flatten
// Remove useless includes
// Make capitalizations consistent
// Fix type conversion warnings

// Build: 
// cd build
// cmake .. && cmake --build . && ctest -C Debug
// ctest -C Debug --rerun-failed --output-on-failure

int main(){
    const auto tuple = new Tuple(1.2, 1.5, 1.7, 0.0);
    std::cout << tuple->isPoint() << std::endl;
    std::cout << tuple->isVector() << std::endl;
    std::cout << tuple->x << std::endl;
    std::cout << tuple->y << std::endl;
    std::cout << tuple->z << std::endl;
    std::cout << tuple->w << std::endl;
    return 0;
}