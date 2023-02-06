#pragma once

#include "math/Color.hpp"
#include "Object.hpp"
#include "Light.hpp"

#include <optional>
#include <memory>
#include <vector>

namespace math {
    struct Intersection;
    struct Ray;
}

class Scene {
public:
    Scene(math::Color background_color = math::BLACK);

    std::optional<math::Intersection> get_closest_intersection(const math::Ray& ray) const;
    
    // Returns wether the point 'a' is visible from 'b' (ie no objects in between)
    bool is_visible_from(const math::Point& a, const math::Point& b) const;

    inline math::Color get_background_color() const
    { return _background_color; }

    inline const std::vector<Light>& get_lights() const
    { return _lights; }

    inline const std::vector<std::unique_ptr<Object>>& get_objects() const
    { return _objects; }

private:
    const math::Color _background_color{ math::BLACK };

    std::vector<std::unique_ptr<Object>> _objects;
    std::vector<Light> _lights;
};