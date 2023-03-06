#pragma once

#include "math/Color.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include <string>
#include <vector>

namespace math {
	struct Intesection;
}

class Renderer {
public:
	Renderer(Scene& scene, Camera& camera);

	void render();
	bool save_to_file(const std::string& filepath) const;

private:
	math::Color compute_color(const math::Intersection& intersec) const;

	Scene& _scene;
	Camera& _camera;

	std::vector<math::Color> _image;
};