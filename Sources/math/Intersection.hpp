#pragma once

#include "math/Point.hpp"

class Object;
class Ray;

namespace math {
    struct Intersection {
        // Intersection point
        Point point;

        // Intersection between the `ray` and an `object`
        Object& obj;
        Ray& ray;

        // Distance between the ray origin and point
        float distance;
    };
}