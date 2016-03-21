#ifndef PPM_H
#define PPM_H

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>

#include "extern/stb_image_write.h"
#include "vec3.h"

struct image {
    const unsigned int width;
    const unsigned int height;
    vec3 *pixels;

    image(unsigned int w, unsigned int h) : width(w), height(h) {
        pixels = new vec3[w * h];
        memset(pixels, 0, sizeof(float) * w * h);
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

void save_as_png(const image &img, const char *filename) {
    uint8_t *rgb = new uint8_t[3 * img.width * img.height]; 

    for (uint32_t i = 0; i < img.width * img.height; ++i) {
        const vec3 &pixel = img.pixels[i];
        assert(pixel.r >= 0.0 && pixel.r <= 1.0);
        assert(pixel.g >= 0.0 && pixel.g <= 1.0);
        assert(pixel.b >= 0.0 && pixel.b <= 1.0);
        rgb[3 * i + 0] = static_cast<unsigned int>(255 * pixel.r);
        rgb[3 * i + 1] = static_cast<unsigned int>(255 * pixel.g);
        rgb[3 * i + 2] = static_cast<unsigned int>(255 * pixel.b);
    }

    // 3 = RGB pixels
    if (!stbi_write_png(filename, img.width, img.height, 3, rgb, 0)) {
        fprintf(stderr, "Error writing %s", filename);
    }

    delete [] rgb;
}

#endif
