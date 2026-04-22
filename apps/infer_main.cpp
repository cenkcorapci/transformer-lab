#include <mtl/runtime/engine.hpp>
#include <mtl/utils/logging.hpp>

#include <CLI/CLI.hpp>
#include <fmt/format.h>

#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
    CLI::App app{"metal-transformer-lab inference runner"};

    std::string model_path;
    std::string prompt;
    int         max_new_tokens = 128;
    std::string log_level      = "info";

    app.add_option("--model",          model_path,     "Path to model weights")->required();
    app.add_option("--prompt",         prompt,         "Input prompt text")->required();
    app.add_option("--max-new-tokens", max_new_tokens, "Maximum tokens to generate")
        ->capture_default_str();
    app.add_option("--log-level",      log_level,      "Log level")->capture_default_str();

    CLI11_PARSE(app, argc, argv);

    mtl::utils::init_logging(log_level);
    auto& log = mtl::utils::get_logger("infer");

    log.info("Loading model from: {}", model_path);
    log.info("Prompt: {}", prompt);
    log.info("Max new tokens: {}", max_new_tokens);

    // TODO: load model weights, run tokenizer, execute inference loop
    log.warn("Inference not yet implemented.");

    return EXIT_SUCCESS;
}
