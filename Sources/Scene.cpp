#include "Scene.hpp"

#include "math/Intersection.hpp"
#include "math/Ray.hpp"
#include "Object.hpp"

Scene::Scene(math::Color background_color) :
    _background_color{ background_color }
{ }

std::optional<math::Intersection> Scene::get_closest_intersection(const math::Ray& ray) const {
    float min_dist{};
    std::optional<math::Intersection> closest_intersec{ std::nullopt };

    for (const auto& obj : _objects) {
        const std::optional<math::Intersection> intersec{ obj->intersection(ray) };
        if (intersec && intersec->distance < min_dist) {
            min_dist = intersec->distance;
            closest_intersec.emplace(*intersec);
        }
    }

    return closest_intersec;
}

bool Scene::is_visible_from(const math::Point& a, const math::Point& b) const {
    const math::Vec dist_vec{ (b - a).to_vec() };
    const float dist_sq{ dist_vec.length_sq() };

    const math::Ray ray{ a, dist_vec.normalized() };

    for (const auto& obj : _objects) {
        const std::optional<math::Intersection> intersec{ obj->intersection(ray) };

        // If the intersection distance is smaller than (a to b) dist, then it is not visible
        if (intersec && intersec->distance * intersec->distance < dist_sq)
            return false;
    }

    return true;
}