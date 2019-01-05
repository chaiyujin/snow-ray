#include "film.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

namespace snowrt {

void Film::save(std::string filename) {
    const uint32_t W = mRes.x;
    const uint32_t H = mRes.y;
    uint8_t *data = new uint8_t[W * H * 3];
    for (uint32_t y = 0; y < H; ++y) {
        for (uint32_t x = 0; x < W; ++x) {
            const auto &rgb = mDataPtr[y*W+x];
            const uint32_t idx = (y*W+x)*3;
            data[idx + 0] = (uint8_t)(Clamp(rgb.x, 0.f, 1.f) * 255);
            data[idx + 1] = (uint8_t)(Clamp(rgb.y, 0.f, 1.f) * 255);
            data[idx + 2] = (uint8_t)(Clamp(rgb.z, 0.f, 1.f) * 255);
        }
    }
    stbi_write_png(filename.c_str(), W, H, 3, data, W*3);
    delete[] data;
}

}