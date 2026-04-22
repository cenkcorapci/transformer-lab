#include <mtl/runtime/engine.hpp>
#include <mtl/utils/error.hpp>
#include <mtl/utils/logging.hpp>
#include <mtl/utils/timer.hpp>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <cstdlib>

int main(int argc, char** argv) {
    CLI::App app{"metal-transformer-lab playground"};

    std::string log_level = "info";
    bool        enable_profiling = false;

    app.add_option("--log-level", log_level, "Logging level (trace/debug/info/warn/error)")
        ->capture_default_str();
    app.add_flag("--profile", enable_profiling, "Enable profiler output");

    CLI11_PARSE(app, argc, argv);

    mtl::utils::init_logging(log_level);
    auto& log = mtl::utils::get_logger("playground");

    log.info("=== metal-transformer-lab playground ===");
    log.info("Initialising engine ...");

    mtl::runtime::Engine::Options opts;
    opts.enable_profiling = enable_profiling;

    mtl::runtime::Engine engine(opts);

    log.info("Engine ready: {}", engine.is_ready() ? "yes" : "no (stub)");
    log.info("Device: {}", engine.metal_context().device().name());

    // TODO: add interactive / scripted playground scenarios

    log.info("Done.");
    return EXIT_SUCCESS;
}
