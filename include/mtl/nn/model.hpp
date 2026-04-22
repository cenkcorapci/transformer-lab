#pragma once

#include <mtl/core/tensor.hpp>

#include <cstddef>
#include <memory>
#include <string_view>
#include <vector>

namespace mtl::nn {

/// Top-level model interface.
///
/// Concrete models (Transformer, BERT, LLaMA, …) inherit from this.
///
/// TODO: implement model serialisation / deserialisation (safetensors format).
/// TODO: add parameter count helper.
class Model {
public:
    virtual ~Model() = default;

    /// Run the model forward pass.
    /// @param input_ids  [batch, seq_len]  integer token IDs
    /// @returns logits   [batch, seq_len, vocab_size]
    [[nodiscard]] virtual core::Tensor forward(const core::Tensor& input_ids) = 0;

    [[nodiscard]] virtual std::string_view name() const noexcept = 0;
    [[nodiscard]] virtual std::size_t      num_parameters() const noexcept = 0;
};

} // namespace mtl::nn
