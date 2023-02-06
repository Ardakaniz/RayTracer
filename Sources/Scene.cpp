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

    for (auto& obj : _objects) {
        std::optional<math::Intersection> intersec{ obj->intersection(ray) };
        if (intersec && intersec->distance < min_dist) {
            min_dist = intersec->distance;
            closest_intersec.emplace(*intersec);
        }
    }

    return closest_intersec;
}