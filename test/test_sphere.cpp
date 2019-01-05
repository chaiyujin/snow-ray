#include <core/core.h>
#include <shapes/sphere.h>
using namespace snowrt;

int main() {
    Sphere *sphere = new Sphere(Float3(0, 0, -10), 1);
    Film film(UInt2(600, 600));
    Camera cam(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0), 45, 1.0);

    for (uint32_t y = 0; y < film.resolution().y; ++y) {
        for (uint32_t x = 0; x < film.resolution().x; ++x) {
            auto ray = cam.getRay(film, x, y);
            if (sphere->intersect(ray)) 
                film.update(Float3(1, 1, 1), x, y);
        }
    }
    film.save("sphere.bmp");

    return 0;
}
