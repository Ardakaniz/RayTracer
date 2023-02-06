#include "Renderer.hpp"

#include "math/Ray.hpp"
#include "math/Intersection.hpp"
#include "Object.hpp"

#include <SFML/Graphics/Image.hpp>

#include <optional>

Renderer::Renderer(Scene& scene, Camera& camera) :
    _scene{ scene },
    _camera{ camera },
    _image{ _camera.get_width() * _camera.get_height(), _scene.get_background_color() }
{ }

void Renderer::render() {
    const unsigned int width  = _camera.get_width();
    const unsigned int height = _camera.get_height();

    // For each pixel...
    for (unsigned int x{ 0 }; x < width; ++x) {
        for (unsigned int y{ 0 }; y < height; ++y) {
            // We create the ray from the observer to the projection of the px (x,y) to the world
            const math::Ray view_ray{ _camera.cast_ray(x, y) };

            // We check if this ray intersect anything (if not, the background color will be rendered)
            const std::optional<math::Intersection> intersec{ _scene.get_closest_intersection(view_ray) };
            if (intersec) {
                math::Color px_color{ _scene.get_background_color() };
                const math::Vec normal{ intersec->obj.get_normal_at(intersec->point) };

                // If there is an intersection, we diffuse every light sources visible from the intersected object onto it 
                for (const Light& light : _scene.get_lights()) {
                    const math::Vec light_to_intersec{ (intersec->point - light.pos).to_vec() };

                    const bool above{ normal.dot(light_to_intersec) > 0 };
                    const bool visible{ _scene.is_visible_from(intersec->point, light.pos) };

                    if (above && visible) {
                        px_color += intersec->obj.get_diffuse_color(light, intersec->point);
                    }
                }
                
                _image[x + y * width] = px_color.clipped(); // We clip the color between 
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