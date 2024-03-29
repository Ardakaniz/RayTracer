#pragma once

#include "math/Point.hpp"

class Object;

namespace math {
    struct Ray;

    struct Intersection {
        // Intersection point
        Point point;

        // Intersection between the `ray` and an `object`
        const Object& obj;
        const Ray& ray;

        // Distance between the ray origin and point
        float distance;
    };
}
