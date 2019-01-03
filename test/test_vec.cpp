#include <iostream>
#include <core/core.h>
using namespace snowray::math;

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
        snowray::log::info("float2 {}", v0);
    }
    {
        Float3 v0(Float2(1, 3));
        Float3 v1(1, 3, 2);
        v0.isfinite();
        std::cout << Dot(v0, v1) << std::endl;
        std::cout << Cross(v0, v1) << std::endl;
        snowray::log::info("float3 {}", v0);
    }
	getchar();
    return 0;
}
