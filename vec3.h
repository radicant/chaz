#ifndef VEC3_H
#define VEC3_H

#include <math.h>

struct vec3 {
	union {
		struct {
			float r;
			float g;
			float b;
		};
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};

	vec3() { }
	vec3(float a, float b, float c) : x(a), y(b), z(c) { }

    vec3 operator*(float f) const {
    	return vec3(f * x, f * y, f * z);
    }

    vec3 operator/(float f) const {
    	return vec3(x / f, y / f, z / f);
    }

    vec3 operator-() const {
        return vec3(-x, -y, -z);
    }
};

vec3 operator*(float f, const vec3 &v) {
	return vec3(f * v.x, f * v.y, f * v.z);
}

vec3 operator+(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3 operator-(const vec3 &v1, const vec3 &v2) {
	return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

float dot(const vec3 &v1, const vec3 &v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float length(const vec3 &v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 normalize(const vec3 &v) {
	return v / length(v);
}

vec3 saturate(const vec3 &v) {
    return vec3(
        fmaxf(0, fminf(1, v.x)), 
        fmaxf(0, fminf(1, v.y)), 
        fmaxf(0, fminf(1, v.z)) 
    );
}

#endif
