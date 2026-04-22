#include <mtl/runtime/profiler.hpp>

#include <fmt/format.h>

#include <algorithm>
#include <iostream>

namespace mtl::runtime {

void Profiler::enable() noexcept { enabled_ = true; }
void Profiler::disable() noexcept { enabled_ = false; }
bool Profiler::is_enabled() const noexcept { return enabled_; }

std::size_t Profiler::begin(std::string_view name) {
    if (!enabled_) {
        return static_cast<std::size_t>(-1);
    }
    const std::size_t token = active_.size();
    active_.push_back({std::string(name), Clock::now()});
    return token;
}

void Profiler::end(std::size_t scope_token) {
    if (!enabled_ || scope_token >= active_.size()) {
        return;
    }
    const auto now     = Clock::now();
    const auto& scope  = active_[scope_token];
    const double ms    = std::chrono::duration<double, std::milli>(now - scope.start).count();

    auto it = index_map_.find(scope.name);
    if (it == index_map_.end()) {
        const std::size_t idx = records_.size();
        records_.push_back({scope.name, ms, 0.0, 1});
        index_map_[scope.name] = idx;
    } else {
        auto& rec = records_[it->second];
        rec.cpu_ms    += ms;
        rec.call_count += 1;
    }
}

void Profiler::record_gpu(std::string_view name, double gpu_ms) {
    auto it = index_map_.find(std::string(name));
    if (it == index_map_.end()) {
        const std::size_t idx = records_.size();
        records_.push_back({std::string(name), 0.0, gpu_ms, 1});
        index_map_[std::string(name)] = idx;
    } else {
        auto& rec = records_[it->second];
        rec.gpu_ms    += gpu_ms;
        rec.call_count += 1;
    }
}

void Profiler::report() const {
    std::cout << fmt::format("{:<40} {:>10} {:>10} {:>8}\n",
                             "Kernel", "CPU (ms)", "GPU (ms)", "Calls");
    std::cout << std::string(72, '-') << '\n';
    for (const auto& r : records_) {
        std::cout << fmt::format("{:<40} {:>10.3f} {:>10.3f} {:>8}\n",
                                 r.name,
                                 r.cpu_ms,
                                 r.gpu_ms,
                                 r.call_count);
    }
}

void Profiler::reset() {
    active_.clear();
    index_map_.clear();
    records_.clear();
}

const std::vector<TimingRecord>& Profiler::records() const noexcept {
    return records_;
}

} // namespace mtl::runtime
