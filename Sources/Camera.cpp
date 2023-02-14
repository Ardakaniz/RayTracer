#include "Camera.hpp"

#include <cmath>

Camera::Camera(const CameraParams& params) :
    _params{ params },
    _viewport_width{  std::tan(_params.fov_angle) * _params.position.z },
    _viewport_height{ std::tan(_params.fov_angle) * _params.position.z }
{ }

math::Point Camera::px_to_world(unsigned int x, unsigned int y) const {
    return {
        .x = _viewport_width  * ((static_cast<float>(x) + 0.5f) / _params.width - 0.5f),
        .y = _viewport_height * ((static_cast<float>(y) + 0.5f) / _params.height - 0.5f),
        .z = 0.0
    };
}

math::Ray Camera::cast_ray(unsigned int x, unsigned int y) const {
    return math::Ray{ _params.position, px_to_world(x, y) };
}