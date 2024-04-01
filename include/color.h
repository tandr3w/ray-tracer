#ifndef H_COLOR
#define H_COLOR

#include "tuple.h"

class Color {
    public:
        Color();
        Color(float r, float g, float b);

        float red, green, blue;
};

bool operator==(const Color& lhs, const Color& rhs);
Color operator+(const Color& lhs, const Color& rhs);
Color operator-(const Color& lhs, const Color& rhs);
Color operator*(const Color& lhs, const float scale);
Color operator*(const Color& lhs, const Color& rhs);

#endif