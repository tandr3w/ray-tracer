#ifndef H_INTERSECTIONS
#define H_INTERSECTIONS

#include <intersection.h>
#include <vector>
#include <optional>

class Intersections {
    public:
        Intersections(std::vector<Intersection> _intersections);
        std::vector<Intersection> intersections;
        Intersection operator[](int);
        int size();
        std::optional<Intersection> hit();
        void sort();
};

#endif
