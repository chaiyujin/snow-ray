#pragma once
#include "../common.h"

namespace snowrt {
namespace options {

extern Float MinShadowBias;
extern Float MaxShadowBias;
extern Float ScaleShadowBias;

inline Float DynamicShadowBias(Float size) {
    return std::min(
        MaxShadowBias,
        std::max(
            MinShadowBias,
            size * ScaleShadowBias
        )
    );
}

}
}