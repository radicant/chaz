#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct ray {
	const vec3 o;
	const vec3 d;

	ray (const vec3 &origin, const vec3 &direction) : o(origin), d(direction) { }
};

#endif
