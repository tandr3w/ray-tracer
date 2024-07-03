#ifndef H_RAY
#define H_RAY

#include <vector>
#include <string>
#include <tuple.h>

class Ray {
    public:
        Ray(Tuple origin, Tuple direction);
        Tuple origin;
        Tuple direction;
        Tuple Position(float t);
};

#endif