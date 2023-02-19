#include "math/Point.hpp"
#include "math/Vec.hpp"

namespace math {
    Point& Point::translate(const Vec& vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }

    Point Point::translated(const Vec& vec) const {
        return { x + vec.x, y + vec.y, z + vec.z };
    }

    Vec Point::to_vec() const {
        return { x, y, z };
    }

    Point operator+(const Point& lhs, const Point& rhs) {
        return {
            .x = lhs.x + rhs.x,
            .y = lhs.y + rhs.y,
            .z = lhs.z + rhs.z
        };
    }

    Point operator-(const Point& lhs, const Point& rhs) {
        return {
            .x = lhs.x - rhs.x,
            .y = lhs.y - rhs.y,
            .z = lhs.z - rhs.z
        };
    }

    Point& operator+=(Point& lhs, const Point& rhs) {
        lhs = lhs + rhs;
        return lhs;
    }

    Point& operator-=(Point& lhs, const Point& rhs) {
        lhs = lhs - rhs;
        return lhs;
    }
}
