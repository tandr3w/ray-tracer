#ifndef H_SPHERE
#define H_SPHERE

#include <vector>
#include <string>
#include <tuple.h>
#include <ray.h>
#include <intersections.h>
#include <intersection.h>

class Sphere {
    public:
        Sphere();
        Intersections Intersect(Ray& r);
};

#endif