#include "Object.hpp"
#include "math/Ray.hpp"

#include <SFML/Graphics/Image.hpp>

#include <cmath>

Object::Object(const math::Point& pos,const float psi, const float theta, const float phi, const math::Color& diffuse_color) :
	_pos{ pos },
    _psi{ psi },
    _diffuse_color{ diffuse_color },
    _theta{ theta },
    _phi { phi }
{ }

unsigned int Object::get_uv_at(const math::Point& pt) const {
    const math::Vec d { (_pos - pt).to_vec().normalized() };
    const float u = 0.5f + atan2(d.z, d.x) / (2.f * M_PI);
    const float v = 0.5f - asin(d.y) / M_PI;

    return static_cast<unsigned int>(u * texture_width) + static_cast<unsigned int>(v * texture_height) * texture_width;
}

math::Color Object::get_diffuse_color(const Light& light,const math::Point& P) const
{
    const math::Color texture_color{ _texture ? (*_texture)[get_uv_at(P)] : math::Color{1.f, 1.f, 1.f} };

    const math::Color Cs=light.color;
    const math::Color Kd={_diffuse_color.r * texture_color.r, _diffuse_color.g * texture_color.g, _diffuse_color.b * texture_color.b};
    const math::Vec N=get_normal_at(P);
    const math::Ray S{light.pos,P};
    const float cos_pi_mth=N.dot(S.direction);
    const math::Color Cd={-Kd.r*Cs.r*cos_pi_mth,-Kd.g*Cs.g*cos_pi_mth,-Kd.b*Cs.b*cos_pi_mth};
    return Cd;
}

void Object::set_texture(const sf::Image& image)
{
    texture_width = image.getSize().x;
    texture_height = image.getSize().y;
    _texture = std::vector<math::Color>(texture_width * texture_height);
    for (unsigned int i = 0; i < texture_width; ++i) {
        for (unsigned int j = 0; j < texture_height; ++j) {
            const sf::Color color = image.getPixel(i, j);
            (*_texture)[i + j * texture_width] = math::Color{color.r / 255.f, color.g / 255.f, color.b / 255.f};
        }
    }
}
