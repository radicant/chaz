#include <stdint.h>

#include "camera.h"
#include "vec3.h"
#include "intersect.h"
#include "image.h"
#include "ray.h"

int main() {
    const uint32_t width = 640;
    const uint32_t height = 480;

    const vec3 cam_pos(0, 0, 5);
    const vec3 look_at(0, 0, -1);
    const vec3 up(0, 1, 0);
    camera cam(cam_pos, look_at, up, 90, (float)width / height);
    image img(width, height);

    sphere s(vec3(0, 0, -0.5), 1);
    vec3 light_dir = normalize(vec3(-1, -1, -1));
    vec3 ambient_color = vec3(1.0, 0, 0);

    vec3 *pixels = img.pixels;
    for (uint32_t y = 0; y < height; ++y) {
        for (uint32_t x = 0; x < width; ++x) {
            const ray r = make_ray(cam, (float)x / width, (float)(height - y) / height);

            vec3 hit;
            vec3 normal;
            if (intersect(s, r, &hit, &normal)) {
                vec3 dir_light_color = fmaxf(0, dot(normal, -light_dir)) * vec3(1.0, 1.0, 1.0);
                *pixels = saturate(ambient_color + dir_light_color);
            }

            ++pixels;
        }
    }

    save_as_ppm(img, "test.ppm");

    return 0;
}
