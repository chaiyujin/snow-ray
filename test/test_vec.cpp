#include <iostream>
#include <core/core.h>
#define SPDLOG_TRACE_ON
#include "spdlog/spdlog.h"
using namespace ray::math;

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
    }
    {
        Float3 v0(3, 2, 1);
        Float3 v1(1, 3, 2);
        v0.isfinite();
        std::cout << Dot(v0, v1) << std::endl;
        std::cout << Cross(v0, v1) << std::endl;
    }

    auto console = spdlog::stdout_color_mt("console");
    console->set_level(spdlog::level::trace); // Set specific logger's log level
    console->debug("This message should be displayed..");
    SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);

    return 0;
}
