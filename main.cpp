#include "vec3.h"
#include "image.h"

int main() {
	image img(3, 2);

	img.pixels[0] = vec3(1, 0, 0);
	img.pixels[1] = vec3(0, 1, 0);
	img.pixels[2] = vec3(0, 0, 1);

	img.pixels[3] = vec3(1, 1, 0);
	img.pixels[4] = vec3(1, 1, 1);
	img.pixels[5] = vec3(0, 0, 0);

	save_as_ppm(img, "test.ppm");

	return 0;
}
