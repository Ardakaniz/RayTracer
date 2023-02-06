//
//  Object.hpp
//  Ray_tracing
//
//

#ifndef Object_hpp
#define Object_hpp
#pragma once

#include "math/Color.hpp"
#include "math/Vec.hpp"
#include "Light.hpp"
#include "math/Intersection.hpp"
#include <optional>
#include <cmath>
namespace math {
struct Point;
struct Ray;
}

class Object {
public:
    Object(const math::Point& pos, const math::Color& diffuse_color);
    virtual ~Object() = default;

    virtual std::optional<math::Intersection>  intersection(const math::Ray& ray) const = 0;
    virtual math::Vec get_normal_at(const math::Point& pt) const  = 0 ;
    math::Color get_diffuse_color(const Light& light,const math::Point& P) const ;

protected:
    const math::Point _pos;
    const math::Color _diffuse_color;
};

#endif /* Object_hpp */
