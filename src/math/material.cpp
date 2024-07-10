#include "material.h"
#include "constants.h"

Material::Material(){

}

bool Material::operator==(const Material& other){
    return float_equal(ambient, other.ambient) && float_equal(diffuse, other.diffuse) && float_equal(specular, other.specular) && float_equal(shininess, other.shininess) && color == other.color;
}
