#include <iostream>
#include <core/core.h>
using namespace snowrt;

int main() {
    {
        Float2 v0;
        Float2 v1(3, 1);
        v0.data[0] = 3.f;
        v0.data[1] = 1.f;
        v0.isfinite();
        std::cout << -v0 << std::endl;
        std::cout << Dot(-v0, v1) << std::endl;
        std::cout << Cross(v0, v1) << std::endl;
        snowrt::log::info("float2 {}", v0);
    }
    {
        Float3 v0(Float2(1, 3));
        Float3 v1(1, 3, 2);
        v0.isfinite();
        std::cout << Dot(v0, v1) << std::endl;
        std::cout << Cross(v0, v1) << std::endl;
        snowrt::log::info("float3 {}", v0);
    }
    {
        AABB2f bbox2f;
        Float2 p(0, 0);
        bbox2f + p;
        bbox2f += p;
        bbox2f.expand(20);
        snowrt::log::info("bbox is {}", bbox2f);
        std::cout << bbox2f.lerp(Float2(0, 1)) << std::endl;
    }
    {
        AABB3f bbox(Float3(0, 0, 0));
        bbox += Float3(1, 3, 5);
        std::cout << bbox << std::endl;
        snowrt::log::info("box is {}", bbox.expand(20));
    }
    {
        Film film(UInt2(600, 400));
        Camera cam(Float3(0, 0, 0), Float3(0, 0, -1), Float3(0, 1, 0), 45, 1.0);
        for (uint32_t y = 0; y < film.resolution().y; ++y) {
            for (uint32_t x = 0; x < film.resolution().x; ++x) {
                Float3 ray = cam.getRay(film, x, y);
                film.update(ray, x, y);
            }
        }
        film.save("test.bmp");
    }
    return 0;
}
