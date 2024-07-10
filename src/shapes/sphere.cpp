#include <vector>
#include <string>
#include <tuple.h>
#include <ray.h>
#include <sphere.h>
#include <intersection.h>
#include <intersections.h>
#include <assert.h>
#include <constants.h>
#include <stdexcept>
#include <string>
#include <material.h>

Sphere::Sphere(){

}

Intersections Sphere::Intersect(Ray& _r){
    Ray r = _r.transform(inverse(transform));
    Tuple sphere_to_ray = r.origin - Point(0, 0, 0); // Convert origin to a vector
    float a = dot(r.direction, r.direction);
    float b = 2 * dot(sphere_to_ray, r.direction);
    float c = dot(sphere_to_ray, sphere_to_ray) - 1;

    // Solve for possible values of t
    float discriminant = b*b - 4*a*c;
    // throw std::runtime_error(std::to_string((-b - sqrt(discriminant)) / 2*a));

    if (discriminant < 0){
        return Intersections(std::vector<Intersection>{});
    }
    else {
        return Intersections(std::vector<Intersection>{
            Intersection((-b - sqrt(discriminant)) / (2*a), this), 
            Intersection((-b + sqrt(discriminant)) / (2*a), this),
        });
    }
}

void Sphere::set_transform(Matrix _transform){
    transform = _transform;
}

Tuple Sphere::normal_at(Tuple world_point){
    Tuple object_point = inverse(transform) * world_point;
    Tuple object_normal = object_point - Point(0, 0, 0);
    Tuple world_normal = transpose(inverse(transform)) * object_normal;
    world_normal.w = 0;
    return Normalize(world_normal);
}
