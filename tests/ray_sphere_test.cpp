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
#include <optional>

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

TEST_CASE("Hit, positive t"){
    Sphere s = Sphere();
    Intersection i1 = Intersection(1, &s);
    Intersection i2 = Intersection(2, &s);
    Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
    Intersection i = xs.hit().value();
    REQUIRE(i == i1);
}

TEST_CASE("Hit, some negative t"){
    Sphere s = Sphere();
    Intersection i1 = Intersection(-1, &s);
    Intersection i2 = Intersection(1, &s);
    Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
    Intersection i = xs.hit().value();
    REQUIRE(i == i2);
}

TEST_CASE("Hit, all negative t"){
    Sphere s = Sphere();
    Intersection i1 = Intersection(-2, &s);
    Intersection i2 = Intersection(-1, &s);
    Intersections xs = Intersections(std::vector<Intersection>{i1, i2});
    REQUIRE((bool) xs.hit() == false);
}

TEST_CASE("Hit, sorted properly"){
    Sphere s = Sphere();
    Intersection i1 = Intersection(5, &s);
    Intersection i2 = Intersection(7, &s);
    Intersection i3 = Intersection(-3, &s);
    Intersection i4 = Intersection(2, &s);
    Intersections xs = Intersections(std::vector<Intersection>{i1, i2, i3, i4});
    Intersection i = xs.hit().value();
    REQUIRE(i == i4);
}

TEST_CASE("Translating Rays"){
    Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
    Matrix m = translation(3, 4, 5);
    Ray r2 = r.transform(m);
    REQUIRE(r2.origin == Point(4, 6, 8));
    REQUIRE(r2.direction == Vector(0, 1, 0));
}

TEST_CASE("Scaling Rays"){
    Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));
    Matrix m = scaling(2, 3, 4);
    Ray r2 = r.transform(m);
    REQUIRE(r2.origin == Point(2, 6, 12));
    REQUIRE(r2.direction == Vector(0, 3, 0));
}

TEST_CASE("Sphere Transformations"){
    Sphere s = Sphere();
    REQUIRE(s.transform == Matrix(4));
    s.set_transform(translation(2, 3, 4));
    REQUIRE(s.transform == translation(2, 3, 4));
}

TEST_CASE("Ray and Scaled Sphere Interactions"){
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Ray r2 = r.transform(inverse(scaling(2, 2, 2)));
    Sphere s = Sphere();
    s.set_transform(scaling(2, 2, 2));
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(float_equal(xs[0].t, 3));
    REQUIRE(float_equal(xs[1].t, 7));
}

TEST_CASE("Ray and Translated Sphere Interactions"){
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere();
    s.set_transform(translation(5, 0, 0));
    Intersections xs = s.Intersect(r);
    REQUIRE(xs.size() == 0);
}
