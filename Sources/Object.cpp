#include "Object.hpp"

Object::Object(const math::Vec& pos, const math::Color& diffuse_color = math::WHITE) :
	_pos{ pos },
	_diffuse_color{ diffuse_color }
{ }