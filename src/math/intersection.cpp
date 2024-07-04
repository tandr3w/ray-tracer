#include <intersection.h>
#include <sphere.h>

Intersection::Intersection(float _t, const void* _object){
    t = _t;
    object = _object;
}