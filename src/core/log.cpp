#include "log.h"
#include <vector>
#include <memory>
namespace snowray::log {

static bool gLevelSet = false;
static std::vector<std::shared_ptr<spdlog::logger>> gLoggers = {
    spdlog::stdout_color_mt("snow-ray"),
    spdlog::rotating_logger_mt("snow-ray-file", "logging.txt",  1048576 * 5, 3)
};

std::vector<std::shared_ptr<spdlog::logger>> &Loggers() {
    if (!gLevelSet) {
        spdlog::set_level(__RAY_LOG_LEVEL__);
        gLevelSet = true;
    }
    return gLoggers;
}

}
