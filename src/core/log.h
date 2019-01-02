#pragma once
#ifdef NDEBUG
// release
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#define __RAY_LOG_LEVEL__ spdlog::level::info
#else
// debug
#define SPDLOG_TRACE_ON
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#define __RAY_LOG_LEVEL__ spdlog::level::trace
#endif

namespace snowray::log {

std::vector<std::shared_ptr<spdlog::logger>> &Loggers();

/* easy access */
template<typename... Args> inline void info(const char *fmt, const Args &... args)  { for (auto logger : Loggers()) logger->info(fmt, args...); }
template<typename... Args> inline void warn(const char *fmt, const Args &... args)  { for (auto logger : Loggers()) logger->warn(fmt, args...); }
template<typename... Args> inline void error(const char *fmt, const Args &... args) { for (auto logger : Loggers()) logger->error(fmt, args...); }
template<typename... Args> inline void fatal(const char *fmt, const Args &... args) { for (auto logger : Loggers()) logger->critical(fmt, args...); exit(1); }

#ifdef NDEBUG
template<typename... Args> inline void debug(const char *fmt, const Args &... args) {}
template<typename... Args> inline void assertion(bool flag, const char *fmt, const Args &... args) {}
template<typename... Args> inline void assertion(bool flag) {}
#else
template<typename... Args> inline void debug(const char *fmt, const Args &... args) { for (auto logger : Loggers()) logger->debug(fmt, args...); }
template<typename... Args> inline void assertion(bool flag, const char *fmt, const Args &... args) {
    if (!flag) {
        for (auto logger : Loggers())
            logger->critical(fmt, args...);
        exit(1);
    }
}
template<typename... Args> inline void assertion(bool flag) {
    if (!flag) {
        for (auto logger : Loggers())
            logger->critical("assertion failed");
        exit(1);
    }
}
#endif

}