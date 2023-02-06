#pragma once

#include "math/Ray.hpp"
#include "math/Point.hpp"

struct CameraParams {
	// Final image width, height
	unsigned int width, height;
	
	// Field of view angle
	float fov_angle;

	// Camera position
	math::Point position;
};

class Camera {
public:
	Camera(const CameraParams& params);

	math::Point px_to_world(unsigned int x, unsigned int y) const;
	math::Ray cast_ray(unsigned int x, unsigned int y) const;

	inline const CameraParams& get_params() const
	{ return _params; }

	inline unsigned int get_width() const
	{ return _params.width; }

	inline unsigned int get_height() const
	{ return _params.height; }

	inline float get_viewport_width() const
	{ return _viewport_width; }

	inline float get_viewport_height() const
	{ return _viewport_height; }

private:
	const CameraParams _params;

	// Width and height of the virtual world, not the pixels (thus != than _params.width/height)
	const float _viewport_width, _viewport_height;
};