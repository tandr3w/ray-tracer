#include "canvas.h"
#include <vector>
#include <string>
#include <math.h>
#include <iostream>
#include <fstream>

Canvas::Canvas(int _width, int _height){
    width = _width;
    height = _height;
    pixels = std::vector<float>(width*height*3, 0);
}

std::string Canvas::to_ppm(int max_color_val){
    std::string out;
    out += "P3\n";
    out += std::to_string(width) + " " + std::to_string(height) + "\n";
    out += std::to_string(max_color_val) + "\n";

    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            for (int k=0; k<3; k++){
                int new_px_color = ceil(pixels[canvas_flatten(height, j, i, k)] * max_color_val);
                new_px_color = std::max(0, new_px_color);
                new_px_color = std::min(max_color_val, new_px_color);
                out += std::to_string(new_px_color);
                if (j < width - 1 || k < 2){
                    out += " ";
                }
            }
        }
        out += "\n";
    }

    return out;
}

void Canvas::write_pixel(int x, int y, Color& color){
    pixels[canvas_flatten(height, x, y, 0)] = color.red;
    pixels[canvas_flatten(height, x, y, 1)] = color.green;
    pixels[canvas_flatten(height, x, y, 2)] = color.blue;
}

Color Canvas::pixel_at(int x, int y){
    return Color(pixels[canvas_flatten(height, x, y, 0)], pixels[canvas_flatten(height, x, y, 1)], pixels[canvas_flatten(height, x, y, 2)]);
}

void Canvas::to_file(std::string ppm){
    std::ofstream out("../output.ppm");
    out << ppm;
    out.close();
}

int canvas_flatten(int height, int x, int y, int z){
    return x*height*3 + y*3 + z;
}


