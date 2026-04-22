#include <mtl/runtime/engine.hpp>
#include <mtl/utils/logging.hpp>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
    CLI::App app{"metal-transformer-lab training runner"};

    std::string data_path;
    int         batch_size    = 8;
    int         max_steps     = 1000;
    float       learning_rate = 3e-4f;
    std::string log_level     = "info";

    app.add_option("--data",          data_path,     "Path to training data")->required();
    app.add_option("--batch-size",    batch_size,    "Mini-batch size")->capture_default_str();
    app.add_option("--max-steps",     max_steps,     "Training steps")->capture_default_str();
    app.add_option("--lr",            learning_rate, "Learning rate")->capture_default_str();
    app.add_option("--log-level",     log_level,     "Log level")->capture_default_str();

    CLI11_PARSE(app, argc, argv);

    mtl::utils::init_logging(log_level);
    auto& log = mtl::utils::get_logger("train");

    log.info("data={}  batch={}  steps={}  lr={}", data_path, batch_size, max_steps,
             learning_rate);

    // TODO: implement training loop
    log.warn("Training not yet implemented.");

    return EXIT_SUCCESS;
}
