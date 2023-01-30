//
//  Object.hpp
//  Ray_tracing
//
//

#ifndef Object_hpp
#define Object_hpp
#pragma once

#include "math/Ray.hpp"
#include "math/Point.hpp"
#include "math/Vec.hpp"
#include <optional>

class Object {
public:
    virtual ~Object() = default;

    virtual std::optional<math::Intersection> intersection(const math::Ray& ray) = 0;
    virtual math::Vec get_normal_at(const math::Point& pt) = 0;
};

#endif /* Object_hpp */
