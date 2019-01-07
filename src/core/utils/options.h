#pragma once
#include "../common.h"

namespace snowrt {
namespace options {

extern Float MinShadowEps;
extern Float MaxShadowEps;
extern Float ScaleShadowEps;

inline Float DynamicShadowEps(Float size) {
    return std::min(
        MaxShadowEps,
        std::max(
            MinShadowEps,
            size * ScaleShadowEps
        )
    );
}

}
}