#ifndef INTERSECT_H
#define INTERSECT_H

#include <math.h>
#include "ray.h"
#include "vec3.h"

struct sphere {
    const vec3 c;
    const float r;

    sphere(const vec3 &center, float radius) : c(center), r(radius) { }
};

bool intersect(const sphere &s, const ray &r, vec3 *hit_point, vec3 *normal) {
    vec3 vec_distance = r.o - s.c;
    float a = dot(r.d, r.d);
    float b = 2.0 * dot(r.d, vec_distance);
    float c = dot(vec_distance, vec_distance) - s.r * s.r;
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    } else {
        float inv2a = 1.0 / (2.0 * a);
        float sqrt_discriminant = sqrt(discriminant);
        float t1 = (-b + sqrt_discriminant) * inv2a;
        float t2 = (-b - sqrt_discriminant) * inv2a;
        float t = fminf(t1, t2);
        
        *hit_point = r.o + t * r.d;
        *normal = normalize(*hit_point - s.c);
        return true;
    }
}

#endif