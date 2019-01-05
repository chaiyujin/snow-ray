#include "log.h"
#include <vector>
#include <memory>

#ifdef __APPLE__
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/rotating_file_sink.h"
#endif

namespace snowrt {
namespace log {

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
}