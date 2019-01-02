#include "log.h"

namespace ray::log {

auto file_log    = spdlog::basic_logger_mt("basic_logger", "snow-ray-log.txt");
auto console_log = spdlog::stdout_color_mt("console");

}