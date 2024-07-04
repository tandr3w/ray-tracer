#include <intersection.h>
#include <intersections.h>
#include <sphere.h>
#include <algorithm> 
#include <optional>

Intersections::Intersections(std::vector<Intersection> _intersections){
    intersections = _intersections;
}

Intersection Intersections::operator[](int index){
    return intersections[index];
}

int Intersections::size(){
    return intersections.size();
}

std::optional<Intersection> Intersections::hit(){
    std::optional<Intersection> hitResult;
    for (int i=0; i<intersections.size(); i++){
        if (intersections[i].t < 0){
            continue;
        }
        else if (!hitResult || intersections[i].t < hitResult.value().t){
            hitResult = std::optional<Intersection>(intersections[i]);
        }
    }
    return hitResult;
}

void Intersections::sort(){
    std::sort(intersections.begin(), intersections.end(), [](const Intersection& lhs, const Intersection& rhs){
        return lhs.t < rhs.t;
    });
}