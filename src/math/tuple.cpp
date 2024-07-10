#include "tuple.h"
#include "constants.h"
#include <cmath>
#include <assert.h>

Tuple::Tuple(){

}

Tuple::Tuple(float _x, float _y, float _z, float _w) {
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

float Tuple::getByIndex(int i) const{
    assert(i < 4);
    switch(i){
        case 0:
            return x;
        case 1:
            return y;
        case 2:
            return z;
        case 3:
            return w;
        default:
            return 0;
    }
}

void Tuple::setByIndex(int i, float val){
    assert(i < 4);
    switch(i){
        case 0:
            x = val;
        case 1:
            y = val;
        case 2:
            z = val;
        case 3:
            w = val;
    }
}


bool Tuple::isPoint() const{
    return w == 1.0;
}

bool Tuple::isVector() const{
    return w == 0.0;
}

Tuple reflect(Tuple in, Tuple normal){
    return in - normal * 2 * dot(in, normal);
}


float Magnitude(Tuple& t){
    return sqrt(pow(t.x, 2) + pow(t.y, 2) + pow(t.z, 2) + pow(t.w, 2));
}

Tuple Point(float x, float y, float z){
    return Tuple(x, y, z, 1.0);
}

Tuple Vector(float x, float y, float z){
    return Tuple(x, y, z, 0.0);
}

float dot(Tuple& a, Tuple& b){
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Tuple cross(Tuple& a, Tuple& b){
    return Vector(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

Tuple Normalize(Tuple& t){
    return Tuple(t.x / Magnitude(t), t.y / Magnitude(t), t.z / Magnitude(t), t.w / Magnitude(t));
}

bool operator==(const Tuple& lhs, const Tuple& rhs){
    return float_equal(lhs.x, rhs.x) && float_equal(lhs.y, rhs.y) && float_equal(lhs.z, rhs.z) && float_equal(lhs.w, rhs.w);
}

Tuple operator+(const Tuple& lhs, const Tuple& rhs){
    return Tuple(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Tuple operator-(const Tuple& lhs, const Tuple& rhs){
    return Tuple(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Tuple operator-(const Tuple& t){
    return Tuple(-t.x, -t.y, -t.z, -t.w);
}

Tuple operator*(const Tuple& lhs, const float scale){
    return Tuple(lhs.x * scale, lhs.y * scale, lhs.z * scale, lhs.w * scale);
}

Tuple operator/(const Tuple& lhs, const float scale){
    return Tuple(lhs.x / scale, lhs.y / scale, lhs.z / scale, lhs.w / scale);
}