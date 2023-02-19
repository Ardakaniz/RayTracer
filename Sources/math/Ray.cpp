#include "math/Ray.hpp"
#include "math/Intersection.hpp"
#include "Object.hpp"

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

    Point Ray::point_at(float t) const {
        return origin.translated(direction * t);
    }

    Ray Ray::reflected(const Intersection& intersec) const {        
        const Vec normal{ intersec.obj.get_normal_at(intersec.point) };
        const Vec dir = Vec{ intersec.ray.direction - 2.f * normal.dot(intersec.ray.direction) * normal }.normalized(); 
        
        return Ray{ intersec.point, dir };
    }
}
