#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include "vec3.h"

struct image {
	const unsigned int width;
	const unsigned int height;
	vec3 *pixels;

	image(unsigned int w, unsigned int h) : width(w), height(h) {
		pixels = new vec3[w * h];
	}

	~image() {
		delete [] pixels;
	}
};

void save_as_ppm(const image &img, const char *filename) {
	FILE *fp = fopen(filename, "w");
	if (!fp) {
		fprintf(stderr, "Error opening %s", filename);
		return;
	}

	fprintf(fp, "P3\n%u %u\n255\n", img.width, img.height);

	const vec3 *imgPtr = img.pixels;
	for (unsigned int i = 0; i < img.height; ++i) {
		for (unsigned int j = 0; j < img.width; ++j) {
			const vec3 pixel = *imgPtr;
			unsigned int ir = static_cast<unsigned int>(255 * pixel.r);
			unsigned int ig = static_cast<unsigned int>(255 * pixel.g);
			unsigned int ib = static_cast<unsigned int>(255 * pixel.b);
			fprintf(fp, "%3u %3u %3u   ", ir, ig, ib);
			++imgPtr;
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
}

#endif
