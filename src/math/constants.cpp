#include "constants.h"
#include <cstdlib>

bool float_equal(float a, float b){
    return abs(a - b) <= EPSILON;
}