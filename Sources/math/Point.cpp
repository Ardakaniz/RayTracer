#include "math/Point.hpp"
#include "math/Vec.hpp"

namespace math {
    Point& Point::translate(const Vec& vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;

        return *this;
    }
}
