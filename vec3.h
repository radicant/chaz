#ifndef VEC3_H
#define VEC3_H

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

	float dot(const vec3 &v2) const {
		return x * v2.x + y * v2.y + z * v2.z;
	}
};


#endif
