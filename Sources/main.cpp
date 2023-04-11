#include <iostream>
#include <chrono>

#include "math/Color.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Renderer.hpp"

#include "objects/Sphere.hpp"
#include "objects/Box.hpp"
#include "objects/Heart.hpp"

int main() {
    Scene scene{ { .3f, .3f, .3f } };
    scene.add_object<Sphere>(math::Point{ 3.5, 0., -13.5 }, 2.f, math::GREEN);
    scene.add_object<Heart>(math::Point{ 0., -3., -13. }, 2.f, -.1f, -1.f, 1.f, 0.f, 0.f, 0.f, math::RED);
    scene.add_object<Box>(math::Point{ -0.5, 3., -13.5 }, 1.f, 1.f, 1.f, 2.f, 1.f, 0.f, 0.f, math::BLUE);
    scene.add_light(Light{ math::Point{ -30., 0., 50 }, math::WHITE * 0.5});
    scene.add_light(Light{ math::Point{ 0., -30., 0 }, math::WHITE * 0.8});

    CameraParams params{ 
        .width = 1000,
        .height = 1000,
        .fov_angle = 3.141592 / 6.,
        .position = { -2., 0., 10. }
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

    if (!renderer.save_to_file("image.png")) {
        return -1;
    }
}