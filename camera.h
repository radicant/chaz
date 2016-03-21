#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include "ray.h"
#include "vec3.h"

struct camera {
    const vec3 position;

    vec3 x_inc, y_inc;
    vec3 bottom_left_point;

    camera(
        const vec3 &pos,
        const vec3 &look_at,
        const vec3 &up,
        float fov_v_deg,
        float aspect_ratio
    ) 
    :   position(pos)
    {
        const vec3 look = normalize(look_at - pos);
        const vec3 r = normalize(cross(look, up));
        const vec3 u = normalize(cross(r, look));

        float fov_v_rad = fov_v_deg * 3.14159265359 / 180.0;
        float half_height = tan(fov_v_rad / 2.0);
        float half_width = aspect_ratio * half_height;

        bottom_left_point = look_at - half_height * u - half_width * r;

        x_inc = 2.0 * half_width * r;
        y_inc = 2.0 * half_height * u;
    }
};

ray make_ray(const camera &cam, float x, float y) {
    vec3 p = cam.bottom_left_point + x * cam.x_inc + y * cam.y_inc;
    return ray(cam.position, p - cam.position);
}

#endif
