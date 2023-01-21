#pragma once

class Camera {
public:
	Camera(unsigned int width, unsigned int height);

	inline unsigned int get_width() const
	{ return _width; }

	inline unsigned int get_height() const
	{ return _height; }

private:
	const unsigned int _width, _height; // TODO: default value, or in ctor
};