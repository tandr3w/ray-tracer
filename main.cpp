#include <iostream>
#include "tuple.h"
#include <canvas.h>
#include <sphere.h>
#include <color.h>
#include <intersection.h>
#include <intersections.h>

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
            if (xs.hit()){
                canvas.write_pixel(x, y, color);
                // std::cout << x << " " << y << std::endl;

            }
            count += 1;
            // std::cout << count << "/" << canvas_pixels*canvas_pixels << " pixels done" << std::endl;
        }
    }
    std::cout << canvas.to_ppm();
    canvas.to_file(canvas.to_ppm());
    std::cout << canvas.pixel_at(0, 0).red;
    std::getchar();
    return 0;
}