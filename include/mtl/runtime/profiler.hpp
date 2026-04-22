#pragma once

#include <chrono>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace mtl::runtime {

/// Per-kernel timing record.
struct TimingRecord {
    std::string name;
    double      cpu_ms{0.0};
    double      gpu_ms{0.0};
    std::size_t call_count{0};
};

/// Lightweight profiler that wraps CPU wall-clock timers and (optionally) Metal
/// GPU timestamps via MTLCommandBuffer completedHandler callbacks.
///
/// TODO: integrate MTLCounterSet for GPU occupancy / VGPR metrics.
/// TODO: emit JSON trace compatible with Chrome Trace Viewer.
class Profiler {
public:
    Profiler()  = default;
    ~Profiler() = default;

    Profiler(const Profiler&)            = delete;
    Profiler& operator=(const Profiler&) = delete;

    void enable()  noexcept;
    void disable() noexcept;
    [[nodiscard]] bool is_enabled() const noexcept;

    /// Begin a named CPU timing scope.  Returns scope token to pass to end().
    std::size_t begin(std::string_view name);

    /// End a previously started scope.
    void end(std::size_t scope_token);

    /// Record a GPU kernel duration in milliseconds.
    void record_gpu(std::string_view name, double gpu_ms);

    /// Print a summary table to stdout.
    void report() const;

    /// Reset all accumulated statistics.
    void reset();

    [[nodiscard]] const std::vector<TimingRecord>& records() const noexcept;

private:
    using Clock     = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    struct ActiveScope {
        std::string name;
        TimePoint   start;
    };

    bool                                enabled_{false};
    std::vector<ActiveScope>            active_;
    std::unordered_map<std::string, std::size_t> index_map_;
    std::vector<TimingRecord>           records_;
};

} // namespace mtl::runtime
