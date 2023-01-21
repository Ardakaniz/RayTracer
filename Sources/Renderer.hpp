#pragma once

#include "math/Color.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include <string>
#include <vector>

class Renderer {
public:
	Renderer(Scene& scene, Camera& camera);

	bool save_to_file(const std::string& filepath) const;

private:
	Scene& _scene;
	Camera& _camera;

	std::vector<math::Color> _image;
};