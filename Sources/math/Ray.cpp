//
//  Ray.cpp
//  Ray_tracing
//
//

#include "math/Ray.hpp"
#include "math/Intersection.hpp"
#include "Object.hpp"

#include <cassert> // TMP

namespace math {
    Ray::Ray(Point origin_, Vec direction_) {
        origin = origin_;
        direction = direction_;
    }

    Ray::Ray(Point A, Point B) {
        origin = A;
        Vec dir;
        dir.x=B.x-A.x;
        dir.y=B.y-A.y;
        dir.z=B.z-A.z;
        dir.normalize();
        direction=dir;
    }

    Ray Ray::reflected(const Intersection& intersec) const {
        // TODO: Object::get_normal_at
        // TODO: float * vec
        
        /* const Vec normal{ intersec.obj.get_normal_at(intersec.point) };
        const Vec dir{ intersec.ray.direction - 2.f * normal.dot(intersec.ray.direction) * normal }; 
        
        return Ray{ intersec.point, dir }; */

        assert(false && "TODO");
        return intersec.ray;
    }
}
