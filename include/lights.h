#ifndef H_LIGHT
#define H_LIGHT

#include "tuple.h"
#include "color.h"
#include <material.h>

class PointLight {
    public:
        PointLight(Tuple _position, Color _intensity);

        Tuple position;
        Color intensity;
};

Color Lighting(Material material, PointLight light, Tuple point, Tuple eyev, Tuple normalv);

#endif