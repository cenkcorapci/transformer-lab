#pragma once

#include <chrono>
#include <string_view>

namespace mtl::utils {

/// RAII wall-clock timer.
///
/// @code
///   mtl::utils::Timer t;
///   t.start();
///   do_work();
///   double ms = t.elapsed_ms();
/// @endcode
class Timer {
public:
    using Clock     = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
    using Duration  = std::chrono::duration<double, std::milli>;

    Timer() = default;

    void   start() noexcept;
    void   stop() noexcept;
    void   reset() noexcept;

    /// Elapsed time in milliseconds since start() (or since construction).
    [[nodiscard]] double elapsed_ms() const noexcept;

    /// Elapsed time in microseconds.
    [[nodiscard]] double elapsed_us() const noexcept;

    /// Returns true if the timer is currently running.
    [[nodiscard]] bool is_running() const noexcept;

private:
    TimePoint start_{};
    TimePoint stop_{};
    bool      running_{false};
};

/// Convenience RAII scope timer that prints on destruction.
class ScopeTimer {
public:
    explicit ScopeTimer(std::string_view label);
    ~ScopeTimer();

    ScopeTimer(const ScopeTimer&)            = delete;
    ScopeTimer& operator=(const ScopeTimer&) = delete;

private:
    std::string_view label_;
    Timer            timer_;
};

} // namespace mtl::utils
