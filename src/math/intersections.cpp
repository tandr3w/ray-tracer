#include <intersection.h>
#include <intersections.h>
#include <sphere.h>

Intersections::Intersections(std::vector<Intersection> _intersections){
    intersections = _intersections;
}

Intersection Intersections::operator[](int index){
    return intersections[index];
}

int Intersections::size(){
    return intersections.size();
}