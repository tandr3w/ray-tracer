#include <iostream>
#include "tuple.h"
#include <canvas.h>
#include <sphere.h>
#include <color.h>
#include <intersection.h>
#include <intersections.h>
#include <material.h>
#include <lights.h>
#include <optional>


// TODO:
// Convert vectors to dynamically allocated arrays
// Split matrix functions into 4x4, 3x3, 2x2, etc. for more code clarity
// Turn things that should be constants into constants
// Make the matrix elements list a private attribute, and stop using matrix_flatten
// Remove useless includes
// Make capitalizations consistent
// Fix type conversion warnings
// Convert functions w/ classes as parameters to methods; don't use both at the same time like a dumbass
// Add __str__ methods to all classes?
// Turn double constants into floats

// Build: 
// cd build
// cmake .. && cmake --build . && ctest -C Debug
// ctest -C Debug --rerun-failed --output-on-failure

int main(){
    Tuple ray_origin = Point(0, 0, -5);
    float wall_z = 10;
    float wall_size = 7;
    int canvas_pixels = 100;
    float pixel_size = wall_size / (float) canvas_pixels;
    float half = wall_size / 2;
    Canvas canvas = Canvas(canvas_pixels, canvas_pixels);
    Color color = Color(1, 0, 0);
    Sphere shape = Sphere();
    PointLight light = PointLight(Point(-10, 10, -10), Color(1, 1, 1));
    shape.material.color = Color(1, 0.2, 1);
    int count = 0;
    for (int y=0; y<canvas_pixels; y++){
        float world_y = half - y * pixel_size;
        for (int x=0; x<canvas_pixels; x++){
            float world_x = x * pixel_size - half;
            Tuple position = Point(world_x, world_y, wall_z);
            // std::cout << "Position: " << position.x << " " << position.y << " " << position.z << std::endl;
            Ray r = Ray(ray_origin, Normalize(position - ray_origin));
            // std::cout << "Ray origin: " << r.origin.x << " " << r.origin.y << " " << r.origin.z << std::endl;
            // std::cout << "Ray direction " << r.direction.x << " " << r.direction.y << " " << r.direction.z << std::endl;
            Intersections xs = shape.Intersect(r);
            // std::cout << xs.size();
            std::optional<Intersection> hit = xs.hit();
            if (hit){
                Intersection _hit = hit.value();
                Tuple point = r.Position(_hit.t);
                Sphere hit_object = *(Sphere*) _hit.object;
                Tuple normal = hit_object.normal_at(point);
                Tuple eye = -r.direction;
                color = Lighting(hit_object.material, light, point, eye, normal);
                canvas.write_pixel(x, y, color);
                // std::cout << x << " " << y << std::endl;

            }
            count += 1;
            // std::cout << count << "/" << canvas_pixels*canvas_pixels << " pixels done" << std::endl;
        }
    }
    std::cout << "Done! Press enter to escape.";
    canvas.to_file(canvas.to_ppm());
    std::getchar();
    return 0;
}