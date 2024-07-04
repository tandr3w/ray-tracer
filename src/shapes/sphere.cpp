#include <vector>
#include <string>
#include <tuple.h>
#include <ray.h>
#include <sphere.h>
#include <intersection.h>
#include <intersections.h>

Sphere::Sphere(){

}

Intersections Sphere::Intersect(Ray& r){
    Tuple sphere_to_ray = r.origin - Point(0, 0, 0); // Convert origin to a vector
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(sphere_to_ray, r.direction);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;

    // Solve for possible values of t
    float discriminant = b*b - 4*a*c;

    if (discriminant < 0){
        return Intersections(std::vector<Intersection>{});
    }
    else {
        return Intersections(std::vector<Intersection>{
            Intersection((-b - sqrt(discriminant)) / 2*a, this), 
            Intersection((-b + sqrt(discriminant)) / 2*a, this),
        });
    }
}