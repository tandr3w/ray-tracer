#include <catch2/catch_test_macros.hpp>
#include "matrix.h"
#include "constants.h"
#include "tuple.h"
#include "ray.h"
#include <vector>
#include <cstdint>
#include <cmath>
#include "sphere.h"
#include <lights.h>
#include <intersection.h>
#include <intersections.h>
#include <optional>
#include <color.h>
#include <material.h>

TEST_CASE("Sphere Normals") {
    Sphere s = Sphere();
    Tuple n = s.normal_at(Point(1, 0, 0));
    REQUIRE(n == Vector(1, 0, 0));
    REQUIRE(n == Normalize(n));

    Tuple n1 = s.normal_at(Point(0, 1, 0));
    REQUIRE(n1 == Vector(0, 1, 0));
    REQUIRE(n1 == Normalize(n1));

    Tuple n2 = s.normal_at(Point(0, 0, 1));
    REQUIRE(n2 == Vector(0, 0, 1));
    REQUIRE(n2 == Normalize(n2));

    Tuple n3 = s.normal_at(Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    REQUIRE(n3 == Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
    REQUIRE(n3 == Normalize(n3));
}    

TEST_CASE("Normals of Translated Sphere") {
    Sphere s = Sphere();
    s.set_transform(translation(0, 1, 0));
    Tuple n = s.normal_at(Point(0, 1.70711, -0.70711));
    REQUIRE(n == Vector(0, 0.70711, -0.70711));
}    

TEST_CASE("Normals of Scaled/Rotated Sphere") {
    Sphere s = Sphere();
    s.set_transform(scaling(1, 0.5, 1) * rotation_z(PI/5));
    Tuple n = s.normal_at(Point(0, sqrt(2)/2, -sqrt(2)/2));
    REQUIRE(n == Vector(0, 0.97014, -0.24254));
}    

TEST_CASE("Vector Reflections") {
    Tuple v = Vector(1, -1, 0);
    Tuple n = Vector(0, 1, 0);
    Tuple r = reflect(v, n);
    REQUIRE(r == Vector(1, 1, 0));
}    

TEST_CASE("Slanted Vector Reflections") {
    Tuple v = Vector(0, -1, 0);
    Tuple n = Vector(sqrt(2)/2, sqrt(2)/2, 0);
    Tuple r = reflect(v, n);
    REQUIRE(r == Vector(1, 0, 0));
}    

TEST_CASE("Point Light"){
    Color intensity = Color(1, 1, 1);
    Tuple position = Point(0, 0, 0);
    PointLight light = PointLight(position, intensity);
    REQUIRE(light.position == position);
    REQUIRE(light.intensity == intensity);
}

TEST_CASE("Materials"){
    Material m = Material();
    REQUIRE(m.color == Color(1, 1, 1));
    REQUIRE(float_equal(m.ambient, 0.1));
    REQUIRE(float_equal(m.diffuse, 0.9));
    REQUIRE(float_equal(m.specular, 0.9));
    REQUIRE(float_equal(m.shininess, 200.0));
}

TEST_CASE("Materials on Spheres"){
    Sphere s = Sphere();
    Material m = Material();
    REQUIRE(s.material == m);

    Material m2 = Material();
    m2.ambient = 1;
    s.material = m2;
    REQUIRE(s.material == m2);
}

TEST_CASE("Lighting, eye between light and surface"){
    Material m = Material();
    Tuple position = Point(0, 0, 0);
    Tuple eyev = Vector(0, 0, -1);
    Tuple normalv = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    REQUIRE(Lighting(m, light, position, eyev, normalv) == Color(1.9, 1.9, 1.9));
}

TEST_CASE("Lighting, eye between light and surface, eye offset 45deg"){
    Material m = Material();
    Tuple position = Point(0, 0, 0);
    Tuple eyev = Vector(0, sqrt(2)/2, -sqrt(2)/2);
    Tuple normalv = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 0, -10), Color(1, 1, 1));
    REQUIRE(Lighting(m, light, position, eyev, normalv) == Color(1.0, 1.0, 1.0));
}

TEST_CASE("Lighting, eye opposite surface, eye offset 45deg"){
    Material m = Material();
    Tuple position = Point(0, 0, 0);
    Tuple eyev = Vector(0, 0, -1);
    Tuple normalv = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 10, -10), Color(1, 1, 1));
    REQUIRE(Lighting(m, light, position, eyev, normalv) == Color(0.7364, 0.7364, 0.7364));
}

TEST_CASE("Lighting, eye in path of reflection vector"){
    Material m = Material();
    Tuple position = Point(0, 0, 0);
    Tuple eyev = Vector(0, -sqrt(2)/2, -sqrt(2)/2);
    Tuple normalv = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 10, -10), Color(1, 1, 1));
    REQUIRE(Lighting(m, light, position, eyev, normalv) == Color(1.6364, 1.6364, 1.6364));
}

TEST_CASE("Lighting, eye behind surface"){
    Material m = Material();
    Tuple position = Point(0, 0, 0);
    Tuple eyev = Vector(0, 0, -1);
    Tuple normalv = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 0, 10), Color(1, 1, 1));
    REQUIRE(Lighting(m, light, position, eyev, normalv) == Color(0.1, 0.1, 0.1));
}