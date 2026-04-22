#include <mtl/utils/logging.hpp>

#include <spdlog/sinks/stdout_color_sinks.h>

#include <memory>
#include <mutex>
#include <unordered_map>

namespace mtl::utils {

namespace {
std::mutex                                              g_mutex;
std::unordered_map<std::string, spdlog::logger>        g_loggers;
} // namespace

spdlog::logger& get_logger(std::string_view name) {
    const std::string key(name);
    std::lock_guard<std::mutex> lock(g_mutex);
    auto it = g_loggers.find(key);
    if (it == g_loggers.end()) {
        auto sink   = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        auto logger = spdlog::logger(key, sink);
        logger.set_level(spdlog::level::info);
        auto [inserted, ok] = g_loggers.emplace(key, std::move(logger));
        (void)ok;
        return inserted->second;
    }
    return it->second;
}

void init_logging(std::string_view level) {
    const auto lvl = spdlog::level::from_str(std::string(level));
    std::lock_guard<std::mutex> lock(g_mutex);
    for (auto& [name, logger] : g_loggers) {
        logger.set_level(lvl);
    }
    // Ensure the default logger exists
    auto& root = get_logger("mtl");
    root.set_level(lvl);
}

} // namespace mtl::utils
