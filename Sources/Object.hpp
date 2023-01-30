//
//  Object.hpp
//  Ray_tracing
//
//

#ifndef Object_hpp
#define Object_hpp
#pragma once

#include "math/Color.hpp"
#include "math/Ray.hpp"
#include "math/Point.hpp"
#include "math/Vec.hpp"

#include <optional>

class Object {
public:
    Object(const math::Vec& pos, const math::Color& diffuse_color = math::WHITE);
    virtual ~Object() = default;

    virtual std::optional<math::Intersection> intersection(const math::Ray& ray) = 0;
    virtual math::Vec get_normal_at(const math::Point& pt) = 0;

    /*
        ray: de light.pos -> this._pos
        Cs: light.color
        N: this.get_normal_at(this.intersection(ray))
        kd: _diffuse_color
    */
    math::Color get_diffuse_color(const Light& light);

private:
    const math::Vec _pos;
    const math::Color _diffuse_color;
};

#endif /* Object_hpp */
