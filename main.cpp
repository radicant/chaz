#include <stdint.h>

#include "vec3.h"
#include "intersect.h"
#include "image.h"
#include "ray.h"

int main() {
	const uint32_t width = 1280;
	const uint32_t height = 720;

	image img(width, height);

	sphere s(vec3(0, 0, -0.5), 1.0);
    vec3 light_dir = normalize(vec3(-1, -1, -1));
    vec3 ambient_color = vec3(1.0, 0, 0);

	vec3 *pixels = img.pixels;
	for (uint32_t y = 0; y < height; ++y) {
		float ndcY = -2.0 * y / height + 1;
		for (uint32_t x = 0; x < width; ++x) {
			float ndcX = 2.0 * x / width - 1;
			const ray r(vec3(ndcX, ndcY, 0), vec3(0, 0, -1));

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
