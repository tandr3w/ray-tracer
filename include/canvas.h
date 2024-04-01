#ifndef H_CANVAS
#define H_CANVAS

#include <vector>
#include "color.h"
#include <string>

class Canvas {
    public:
        Canvas(int _width, int _height);
        int width, height;
        std::vector<float> pixels;

        std::string to_ppm(int max_color_val = 255);
        void to_file(std::string ppm);
        void write_pixel(int x, int y, Color& color);
        Color pixel_at(int x, int y);
};

int canvas_flatten(int height, int x, int y, int z);

#endif