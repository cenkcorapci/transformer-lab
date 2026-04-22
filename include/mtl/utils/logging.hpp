#pragma once

#include <spdlog/spdlog.h>

#include <memory>
#include <string_view>

namespace mtl::utils {

/// Thin façade over spdlog to provide a named logger per subsystem.
///
/// Usage:
/// @code
///   auto& log = mtl::utils::get_logger("gpu");
///   log.info("Device: {}", device_name);
/// @endcode
[[nodiscard]] spdlog::logger& get_logger(std::string_view name = "mtl");

/// Initialise the logging subsystem.  Call once at startup.
/// @param level  One of: trace, debug, info, warn, error, critical, off
void init_logging(std::string_view level = "info");

} // namespace mtl::utils
