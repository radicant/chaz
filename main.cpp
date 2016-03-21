#include <stdint.h>

#include "camera.h"
#include "vec3.h"
#include "intersect.h"
#include "image.h"
#include "ray.h"

#include <random>
std::random_device rd;
std::mt19937 generator(rd());
std::uniform_real_distribution<float> rand_float(0, 1);

int main() {
    const uint32_t samples_per_pixel = 16;
    const uint32_t width = 1280;
    const uint32_t height = 720;

    const vec3 cam_pos(0, 0, 25);
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
            
            vec3 color(0, 0, 0);
            for (uint32_t sample = 0; sample < samples_per_pixel; ++sample) {
                const ray r = make_ray(
                    cam, 
                    (x + rand_float(generator)) / width, 
                    (height - (y + rand_float(generator))) / height
                );

                vec3 hit;
                vec3 normal;
                if (intersect(s, r, &hit, &normal)) {
                    vec3 dir_light_color = fmaxf(0, dot(normal, -light_dir)) * vec3(1.0, 1.0, 1.0);
                    color += saturate(ambient_color + dir_light_color);
                }
            }

            color /= samples_per_pixel;
            *pixels++ = color;
        }
    }

    save_as_png(img, "test.png");

    return 0;
}
