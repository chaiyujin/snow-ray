#include <core/core.h>
#include <shapes/sphere.h>
#include <vector>
using namespace snowrt;

Material *specMat  = new IdeaSpecular(Float3(0,0,0), Float3(.999f,.999f,.999f));
Material *diffMat0 = new IdeaDiffuse(Float3(0,0,0),  Float3(.75f,.25f,.25f));
Material *diffMat1 = new IdeaDiffuse(Float3(0,0,0),  Float3(.25f,.25f,.75f));
Material *diffMat2 = new IdeaDiffuse(Float3(0,0,0),  Float3(.75f,.75f,.75f));
Material *diffMat3 = new IdeaDiffuse(Float3(0,0,0),  Float3(0,0,0));
Material *diffMat4 = new IdeaDiffuse(Float3(12,12,12), Float3(0,0,0));

std::vector<Sphere *> sphereList = {
    new Sphere(Float3(27,16.5,47), 16.5, specMat),
    new Sphere(Float3(73,16.5,78), 16.5, specMat),
    new Sphere(Float3(1e5+1,40.8,81.6),   1e5, diffMat0), 
    new Sphere(Float3(-1e5+99,40.8,81.6), 1e5, diffMat1),
    new Sphere(Float3(50,40.8, 1e5),      1e5, diffMat2),
    new Sphere(Float3(50, 1e5, 81.6),     1e5, diffMat2),
    new Sphere(Float3(50,-1e5+81.6,81.6), 1e5, diffMat2),
    new Sphere(Float3(50,681.6-.27,81.6), 600, diffMat4)
};

Float3 radiance(const Ray &ray, int depth, int lastId=-1) {
    Float tMax = MAXFLOAT;
    SurfaceInteraction insect;
    int curId = -1;
    for (int idx = 0; idx < sphereList.size(); ++idx) {
        // if (idx == lastId) continue;
        if (sphereList[idx]->intersect(ray, &tMax, &insect)) {
            curId = idx;
        }
    }
    if (insect.shape == nullptr) return Float3();
    const auto *sphere = (const Sphere *)insect.shape;
    const auto *material = sphere->materialPtr();
    auto f = material->albedo();
    if (++depth>5) {
        // r.r
        Float p = (f.x > f.y && f.x > f.z)
                ? f.x : ((f.y > f.z) ? f.y : f.z);
        if (random::uniform() < p)
            f /= p;
        else 
            return material->emission();
    }
    Ray rayIn;
    material->scatter(&insect, rayIn);
    return material->emission() + f * radiance(rayIn, depth, curId);
}

int main() {
    Float3 wo = Float3(-1, 1, 0).normalized();
    Float3 n  = Float3(0, 1, 0);
    std::cout << Reflect(wo, n) << std::endl;

    Film film(UInt2(320, 240));
    Camera cam(Float3(50,52,295.6), Float3(50,52-0.042612,295.6-1),
               Float3(0, 1, 0), 30, film.aspect());
    const int samples = 32;
    Float invsamples = (Float)1 / (Float)samples;
#pragma omp parallel for schedule(dynamic, 1) private(color)
    for (uint32_t y = 0; y < film.resolution().y; ++y) {
        std::cout << y << std::endl;
        for (uint32_t x = 0; x < film.resolution().x; ++x) {
            Float3 color;
            for (uint32_t s = 0; s < samples; ++s) {
                auto ray = cam.randomRay(film, x, y);
                auto spec = radiance(ray, 0);
                color += spec * invsamples;
            }
            film.update(color, x, y);
        }
    }
    film.save("sphere.png");

    return 0;
}
