#pragma once

#include <mtl/core/tensor.hpp>
#include <mtl/nn/attention.hpp>
#include <mtl/nn/mlp.hpp>

#include <cstddef>
#include <optional>

namespace mtl::nn {

/// A single pre-norm transformer block:
///   x = x + Attention(RMSNorm(x))
///   x = x + MLP(RMSNorm(x))
///
/// TODO: implement forward pass.
/// TODO: support post-norm layout (original Transformer).
class TransformerBlock {
public:
    struct Config {
        MultiHeadAttention::Config attn;
        MLP::Config                mlp;
        float                      norm_eps{1e-6f};
        bool                       pre_norm{true};
    };

    explicit TransformerBlock(Config cfg);
    ~TransformerBlock();

    TransformerBlock(const TransformerBlock&)            = delete;
    TransformerBlock& operator=(const TransformerBlock&) = delete;
    TransformerBlock(TransformerBlock&&) noexcept;
    TransformerBlock& operator=(TransformerBlock&&) noexcept;

    /// @param hidden_states  [batch, seq, embed_dim]
    /// @param mask           optional causal mask
    [[nodiscard]] core::Tensor forward(const core::Tensor&         hidden_states,
                                       std::optional<core::Tensor> mask = std::nullopt) const;

    [[nodiscard]] const Config& config() const noexcept;

private:
    struct Impl;
    Impl* impl_{nullptr};
};

} // namespace mtl::nn
