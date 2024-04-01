#include "color.h"
#include "constants.h"

Color::Color(){

}

Color::Color(float _r, float _g, float _b){
    red = _r;
    green = _g;
    blue = _b;
}


bool operator==(const Color& lhs, const Color& rhs){
    return float_equal(lhs.red, rhs.red) && float_equal(lhs.green, rhs.green) && float_equal(lhs.blue, rhs.blue);
}

Color operator+(const Color& lhs, const Color& rhs){
    return Color(lhs.red + rhs.red, lhs.green + rhs.green, lhs.blue + rhs.blue);
}

Color operator-(const Color& lhs, const Color& rhs){
    return Color(lhs.red - rhs.red, lhs.green - rhs.green, lhs.blue - rhs.blue);
}

Color operator*(const Color& lhs, const float scale){
    return Color(lhs.red * scale, lhs.green * scale, lhs.blue * scale);
}

Color operator*(const Color& lhs, const Color& rhs){
    return Color(lhs.red * rhs.red, lhs.green * rhs.green, lhs.blue * rhs.blue);
}