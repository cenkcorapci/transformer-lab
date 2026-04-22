#include <mtl/utils/timer.hpp>

#include <fmt/format.h>

#include <iostream>

namespace mtl::utils {

// ─── Timer ────────────────────────────────────────────────────────────────────

void Timer::start() noexcept {
    start_   = Clock::now();
    running_ = true;
}

void Timer::stop() noexcept {
    if (running_) {
        stop_    = Clock::now();
        running_ = false;
    }
}

void Timer::reset() noexcept {
    start_   = {};
    stop_    = {};
    running_ = false;
}

double Timer::elapsed_ms() const noexcept {
    const auto end = running_ ? Clock::now() : stop_;
    return Duration(end - start_).count();
}

double Timer::elapsed_us() const noexcept {
    const auto end = running_ ? Clock::now() : stop_;
    return std::chrono::duration<double, std::micro>(end - start_).count();
}

bool Timer::is_running() const noexcept {
    return running_;
}

// ─── ScopeTimer ──────────────────────────────────────────────────────────────

ScopeTimer::ScopeTimer(std::string_view label) : label_(label) {
    timer_.start();
}

ScopeTimer::~ScopeTimer() {
    timer_.stop();
    std::cout << fmt::format("[ScopeTimer] {}: {:.3f} ms\n", label_, timer_.elapsed_ms());
}

} // namespace mtl::utils
