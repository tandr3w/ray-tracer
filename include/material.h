#ifndef H_MATERIAL
#define H_MATERIAL

#include "tuple.h"
#include <color.h>

class Material {
    public:
        Material();
        Color color = Color(1, 1, 1);
        float ambient = 0.1;
        float diffuse = 0.9;
        float specular = 0.9;
        float shininess = 200.0;
        bool operator==(const Material& other);

};


#endif