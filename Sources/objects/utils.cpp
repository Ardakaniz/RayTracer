#include "objects/utils.hpp"

#include "Object.hpp"
#include "objects/Sphere.hpp"
#include "math/Ray.hpp"

namespace utils {
	std::optional<math::Intersection> compute_intersec(const Sphere& circumscribed_sphere, const Object& obj, const math::Ray& ray, const std::function<float (const math::Ray& ray, float t)>& f) {
		const std::optional<math::Intersection> coarse_intersec{ circumscribed_sphere.intersection(ray) };
		if (!coarse_intersec)
        return std::nullopt;

        // How best to choose these values?
        constexpr float COARSE_DT = 0.1;
        constexpr float EPS = 1e-3;
        constexpr unsigned int MAX_ITER = 100;
        
        float t{ coarse_intersec->distance };
        unsigned int iter_count{ 0 };
        const bool initial_sign{ f(ray, t) < 0 };

        while ((f(ray, t) < 0) == initial_sign && iter_count < MAX_ITER) {
            ++iter_count;
            t += COARSE_DT;
        }

        if (iter_count == MAX_ITER)
            return std::nullopt;

        float lower_t{ t - COARSE_DT }, higher_t{ t };
        while (higher_t - lower_t > EPS && iter_count < MAX_ITER) {
            t = (higher_t + lower_t) / 2.;

            if ((f(ray, t) < 0) == initial_sign)
                lower_t = t;
            else
                higher_t = t;

            ++iter_count;
        }

        if (iter_count == MAX_ITER)
            return std::nullopt;

        return math::Intersection{
            .point = ray.point_at(t),
            .obj = obj,
            .ray = ray,
            .distance = t
        };
	}
}