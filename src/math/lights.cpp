#include "lights.h"
#include "tuple.h"
#include "color.h"
#include <material.h>
#include <cmath>
    
PointLight::PointLight(Tuple _position, Color _intensity){
    position = _position;
    intensity = _intensity;
}

Color Lighting(Material material, PointLight light, Tuple point, Tuple eyev, Tuple normalv) {
    Color effective_color = material.color * light.intensity;
    Tuple lightv = Normalize(light.position - point);
    Color ambient = effective_color * material.ambient;
    float light_dot_normal = dot(lightv, normalv);
    Color diffuse = Color(0, 0, 0);
    Color specular = Color(0, 0, 0);
    if (light_dot_normal >= 0){
        diffuse = effective_color * material.diffuse * light_dot_normal;
        
        Tuple reflectv = reflect(-lightv, normalv);
        float reflect_dot_eye = dot(reflectv, eyev);
        if (reflect_dot_eye > 0){
            float factor = pow(reflect_dot_eye, material.shininess);
            specular = light.intensity * material.specular * factor;
        }
    }

    return ambient + diffuse + specular;
}