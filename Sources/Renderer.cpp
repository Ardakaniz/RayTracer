#include "Renderer.hpp"

#include "math/Ray.hpp"
#include "math/Intersection.hpp"
#include "Object.hpp"

#include <SFML/Graphics/Image.hpp>

#include <optional>
#include <iostream>

Renderer::Renderer(Scene& scene, Camera& camera) :
    _scene{ scene },
    _camera{ camera },
    _image{ _camera.get_width() * _camera.get_height(), _scene.get_background_color() }
{ }

void Renderer::render() {
    constexpr unsigned int MAX_REFLEC = 5;
    const unsigned int width  = _camera.get_width();
    const unsigned int height = _camera.get_height();

    constexpr float METALLIC_STRENGTH = 1.f; // TODO: Make this an object parameter

    // For each pixel...
    for (unsigned int x{ 0 }; x < width; ++x) {
        for (unsigned int y{ 0 }; y < height; ++y) {
            // We create the ray from the observer to the projection of the px (x,y) to the world
            math::Ray ray{ _camera.cast_ray(x, y) };

            // We check if this ray intersect anything (if not, the background color will be rendered)
            const std::optional<math::Intersection> screen_intersec{ _scene.get_closest_intersection(ray) };
            if (screen_intersec) { 
                const math::Color px_color{ compute_color(*screen_intersec) }; 
                math::Color reflec_color{ math::BLACK };

                math::Ray reflec_ray{ ray.reflected(*screen_intersec) };

                for (unsigned int reflec_count{ 0 }; reflec_count < MAX_REFLEC; ++reflec_count) {
                    const auto intersec{ _scene.get_closest_intersection(reflec_ray) };
                    if (intersec) {
                        reflec_color += compute_color(*intersec) * METALLIC_STRENGTH;
                        reflec_ray = ray.reflected(*intersec);
                    }
                }

                _image[x + y * width] = (px_color + reflec_color / static_cast<float>(MAX_REFLEC)).clamped(); // We clamp the color between 0 and 1
            }
        }
    }
}

bool Renderer::save_to_file(const std::string& filepath) const {
    sf::Image image;
    image.create(_camera.get_width(), _camera.get_height());

    for (unsigned int x{ 0 }; x < _camera.get_width(); ++x) {
        for (unsigned int y{ 0 }; y < _camera.get_height(); ++y) {
            const math::Color px_color = _image[x + y * _camera.get_width()] * 255.;

            // We convert our color to SFML Color
            const sf::Color sf_px_color = sf::Color(
                static_cast<sf::Uint8>(px_color.r),
                static_cast<sf::Uint8>(px_color.g),
                static_cast<sf::Uint8>(px_color.b)
            );

            image.setPixel(x, y, sf_px_color);
        }
    }

    return image.saveToFile(filepath);
}

math::Color Renderer::compute_color(const math::Intersection& intersec) const {
    math::Color px_color{ math::BLACK };
    const math::Vec normal{ intersec.obj.get_normal_at(intersec.point) };

    // If there is an intersection, we diffuse every light sources visible from the intersected object onto it 
    for (const Light& light : _scene.get_lights()) {
        const math::Vec light_to_intersec{ (intersec.point - light.pos).to_vec() };

        if (normal.dot(light_to_intersec) < 0 && _scene.is_visible_from(light.pos, intersec.point))
            px_color += intersec.obj.get_diffuse_color(light, intersec.point);
    }
    
    return px_color;
}