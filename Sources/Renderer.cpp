#include "Renderer.hpp"

#include <SFML/Graphics/Image.hpp>

Renderer::Renderer(Scene& scene, Camera& camera) :
    _scene{ scene },
    _camera{ camera },
    _image{ _camera.get_width() * _camera.get_height(), _scene.get_background_color() }
{ }

bool Renderer::save_to_file(const std::string& filepath) const {
    sf::Image image;
    image.create(_camera.get_width(), _camera.get_height());

    for (unsigned int x{ 0 }; x < _camera.get_width(); ++x) {
        for (unsigned int y{ 0 }; y < _camera.get_height(); ++y) {
            const math::Color px_color = _image[x + y * _camera.get_width()];

            // We convert our color to SFML Color
            const sf::Color sf_px_color = sf::Color(
                static_cast<sf::Uint8>(px_color.r * 255.),
                static_cast<sf::Uint8>(px_color.g * 255.),
                static_cast<sf::Uint8>(px_color.b * 255.)
            );

            image.setPixel(x, y, sf_px_color);
        }
    }

    return image.saveToFile(filepath);
}