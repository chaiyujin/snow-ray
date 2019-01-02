#pragma once
#ifdef NDEBUG
// release
#include <spdlog/spdlog.h>
#define __RAY_LOG_LEVEL__ spdlog::level::info
#else
// debug
#define SPDLOG_TRACE_ON
#include <spdlog/spdlog.h>
#define __RAY_LOG_LEVEL__ spdlog::level::trace
#endif

namespace ray::log {


/* easy access */
template<typename... Args> inline void info(const char *fmt, const Args &... args);
template<typename... Args> inline void warn(const char *fmt, const Args &... args);
template<typename... Args> inline void debug(const char *fmt, const Args &... args);
template<typename... Args> inline void error(const char *fmt, const Args &... args);
template<typename... Args> inline void fatal(const char *fmt, const Args &... args);
/* assert */
template<typename... Args> void assertion(bool flag) {
    if (!flag) { Logger()->critical("assertion failed"); exit(1); }
}
template<typename... Args> void assertion(bool flag, const char *fmt, const Args &... args) {
    if (!flag) { Logger()->critical(fmt, args...); exit(1); }
}
}