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

	void render(unsigned int x_start, unsigned int x_end, unsigned int y_start, unsigned int y_end);
	void render_all();
	void render_all_threaded();
	bool save_to_file(const std::string& filepath) const;

private:
	math::Color compute_color(const math::Intersection& intersec) const;

	Scene& _scene;
	Camera& _camera;

	std::vector<math::Color> _image;
};