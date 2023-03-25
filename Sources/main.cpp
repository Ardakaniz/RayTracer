#include <iostream>
#include <chrono>

#include "math/Color.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

#include "objects/Sphere.hpp"
#include "objects/Heart.hpp"
#include "objects/Box.hpp"

#include <SFML/Graphics/Image.hpp>
#include <cmath>

int main() {
    Scene scene{ { .2f, .2f, .2f } };
    scene.add_object<Sphere>(math::Point{ -1.5f,  0.f, -2.f }, 1.f, math::RED * 0.7);
    scene.add_object<Sphere>(math::Point{ 1.f,  0.f, -3.f }, 1.f, math::WHITE);
    scene.add_light(Light{ math::Point{ 10., 0., 10.f }, math::Color{0.8f, 0.8f, 0.8f}});

    sf::Image wood_texture;
    if (!wood_texture.loadFromFile("wood_texture.jpg")) {
        return -1;
    }
    
    scene.set_object_texture(1, wood_texture);

    CameraParams params{ 
        .width = 1000,
        .height = 1000,
        .fov_angle = 3.141592 / 8.,
        .position = { 0., 0., 10. }
    };
    Camera camera{ params };

    std::cout << "--- Camera params ---" << std::endl;
    std::cout << "Output width x height: " << camera.get_width() << "x" << camera.get_height() << std::endl;
    std::cout << "Viewport width / height: " << camera.get_viewport_width() << " / " << camera.get_viewport_height() << std::endl; 

    Renderer renderer{ scene, camera };

    const auto start{ std::chrono::steady_clock::now() };
    renderer.render_all_threaded();
    const auto end{ std::chrono::steady_clock::now() };
    std::cout << "Render took " << std::chrono::duration<float>(end - start).count() << "s." << std::endl;
    
    std::cout << "Saving... " << std::flush;
    if (!renderer.save_to_file("image.png")) {
        return -1;
    }

    std::cout << "Done." << std::endl;

    return 0;
}