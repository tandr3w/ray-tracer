#include <constants.h>
#include <vector>
#include <assert.h>
#include <tuple.h>
#include <ray.h>
#include <matrix.h>

Ray::Ray(Tuple _origin, Tuple _direction){
    assert(_origin.isPoint());
    assert(_direction.isVector());
    origin = _origin;
    direction = _direction;
}

Tuple Ray::Position(float t){
    return origin + direction * t;
}

Ray Ray::transform(Matrix matrix){
    return Ray(matrix*origin, matrix*direction);
}