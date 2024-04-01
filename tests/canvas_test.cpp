#include <catch2/catch_test_macros.hpp>
#include "color.h"
#include "canvas.h"
#include <string>
#include <sstream>
#include <vector>

TEST_CASE("Canvas") {
    Canvas c = Canvas(10, 20);
    REQUIRE(c.width == 10);
    REQUIRE(c.height == 20);
    for (int i=0; i<sizeof(c.pixels) / sizeof(c.pixels[0]); i++){
        REQUIRE(c.pixels[i] == 0);
    }
}

TEST_CASE("Writing To Canvas") {
    Canvas c = Canvas(10, 20);
    Color red = Color(1, 0, 0);
    c.write_pixel(2, 3, red);
    REQUIRE(c.pixel_at(2, 3) == red);
}

TEST_CASE("Converting to PPM"){
    Canvas c = Canvas(5, 3);
    Color c1 = Color(1.5, 0, 0);
    Color c2 = Color(0, 0.5, 0);
    Color c3 = Color(-0.5, 0, 1);

    c.write_pixel(0, 0, c1);
    c.write_pixel(2, 1, c2);
    c.write_pixel(4, 2, c3);

    std::string raw_out = c.to_ppm();
    std::stringstream ss(raw_out);
    std::string to;
    std::vector<std::string> parsed_out;

    while(std::getline(ss,to,'\n')){
        parsed_out.push_back(to);
    }

    REQUIRE(parsed_out[0] == "P3");
    REQUIRE(parsed_out[1] == "5 3");
    REQUIRE(parsed_out[2] == "255");
    REQUIRE(parsed_out[3] == "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
    REQUIRE(parsed_out[4] == "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
    REQUIRE(parsed_out[5] == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}