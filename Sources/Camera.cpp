#include "Camera.hpp"

#include <cmath>

Camera::Camera(const CameraParams& params) :
    _params{ params },
    _viewport_width{  std::tan(_params.fov_angle) * _params.position.z },
    _viewport_height{ std::tan(_params.fov_angle) * _params.position.z }
{ }

math::Point Camera::px_to_world(unsigned int x, unsigned int y) const {
    return {
        .x = _viewport_width  * (x + 0.5f) / _params.width,
        .y = _viewport_height * (y + 0.5f) / _params.height,
        .z = 0.0
    };
}

math::Ray Camera::cast_ray(unsigned int x, unsigned int y) const {
    return math::Ray{ _params.position, px_to_world(x, y) };
}