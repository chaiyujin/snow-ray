#include "film.h"
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

namespace snowrt {

void Film::save(std::string filename) {

    auto toByte = [](Float v) -> uint8_t {
        return (uint8_t)(pow(Clamp(v,0.f,1.f),1/2.2)*255);
    };
    const uint32_t W = mRes.x;
    const uint32_t H = mRes.y;
    uint8_t *data = new uint8_t[W * H * 3];
    for (uint32_t y = 0; y < H; ++y) {
        for (uint32_t x = 0; x < W; ++x) {
            const auto &rgb = mDataPtr[y*W+x];
            const uint32_t idx = (y*W+x)*3;
            data[idx + 0] = toByte(rgb.x); 
            data[idx + 1] = toByte(rgb.y); 
            data[idx + 2] = toByte(rgb.z); 
        }
    }
    stbi_write_png(filename.c_str(), W, H, 3, data, W*3);
    delete[] data;
}

}