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

namespace sf {
    class Image;
}

class Scene {
public:
    Scene(math::Color background_color = math::BLACK);

    template<class T, class... Args>
    void add_object(const math::Point& pos, Args&&... args)
    { _objects.emplace_back(std::make_unique<T>(pos, std::forward<Args>(args)...)); }

    void add_light(const Light& light)
    { _lights.push_back(light); }

    // /!\ No check on index
    void set_object_texture(unsigned int index, const sf::Image& image)
    { _objects[index]->set_texture(image); }

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