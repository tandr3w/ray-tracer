#include <catch2/catch_test_macros.hpp>
#include "matrix.h"
#include "constants.h"
#include "tuple.h"
#include "ray.h"
#include <vector>
#include <cstdint>
#include <cmath>
#include "sphere.h"
#include <intersection.h>
#include <intersections.h>

TEST_CASE("Rays") {
    Tuple origin = Point(1, 2, 3);
    Tuple direction = Vector(4, 5, 6);
    Ray r = Ray(origin, direction);
    REQUIRE(r.origin == origin);
    REQUIRE(r.direction == direction);
}


TEST_CASE("Ray Position") {
    Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));
    REQUIRE(r.Position(0) == Point(2, 3, 4));
    REQUIRE(r.Position(1) == Point(3, 3, 4));
    REQUIRE(r.Position(-1) == Point(1, 3, 4));
    REQUIRE(r.Position(2.5) == Point(4.5, 3, 4));
}

TEST_CASE("Ray-Sphere Intersections - Two Intersections") {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 2);

    // Avoid use of float_equal after intersection is turned into an object
    REQUIRE(float_equal(xs[0].t, 4.0));
    REQUIRE(float_equal(xs[1].t, 6.0));
}

TEST_CASE("Ray-Sphere Intersections - No Intersections") {
    Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 0);
}

TEST_CASE("Ray-Sphere Intersections - Ray Inside Sphere") {
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(float_equal(xs[0].t, -1.0));
    REQUIRE(float_equal(xs[1].t, 1.0));
}

TEST_CASE("Ray-Sphere Intersections - Sphere Behind Ray") {
    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(float_equal(xs[0].t, -6.0));
    REQUIRE(float_equal(xs[1].t, -4.0));
}

TEST_CASE("Intersection"){
    Sphere s = Sphere();
    Intersection i = Intersection(3.5, &s);
    REQUIRE(float_equal(i.t, 3.5));
    REQUIRE(i.object == &s);
}

TEST_CASE("Aggregating Intersections"){
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);
    Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
    REQUIRE(xs.size() == 2);
    REQUIRE(float_equal(xs[0].t, 1));
    REQUIRE(float_equal(xs[1].t, 2));
}

TEST_CASE("Intersection sets object"){
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].object == &s);
    REQUIRE(xs[1].object == &s);
}