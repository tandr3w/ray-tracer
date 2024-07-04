#ifndef H_INTERSECTIONS
#define H_INTERSECTIONS

#include <intersection.h>
#include <vector>

class Intersections {
    public:
        Intersections(std::vector<Intersection> _intersections);
        std::vector<Intersection> intersections;
        Intersection operator[](int);
        int size();
};

#endif