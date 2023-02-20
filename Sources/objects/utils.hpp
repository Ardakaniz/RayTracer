#pragma once

#include "math/Intersection.hpp"

#include <optional>
#include <functional>

class Sphere;
class Object;
namespace math {
	struct Ray;
}

namespace utils {
	std::optional<math::Intersection> compute_intersec(const Sphere& circumscribed_sphere, const Object& obj, const math::Ray& ray, const std::function<float (const math::Ray& ray, float t)>& f);
}