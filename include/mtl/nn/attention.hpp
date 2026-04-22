#pragma once

#include <mtl/core/tensor.hpp>

#include <cstddef>
#include <optional>

namespace mtl::nn {

/// Scaled dot-product multi-head attention.
///
/// Implements the attention mechanism from "Attention Is All You Need"
/// (Vaswani et al., 2017).
///
/// TODO: implement scaled dot-product attention forward pass.
/// TODO: add causal (autoregressive) mask support.
/// TODO: integrate FlashAttention tiled kernel (shaders/flash_attention.metal).
/// TODO: add KV-cache for incremental decoding.
class MultiHeadAttention {
public:
    struct Config {
        std::size_t embed_dim{512};
        std::size_t num_heads{8};
        std::size_t head_dim{64}; ///< embed_dim / num_heads by default
        bool        is_causal{false};
        float       dropout{0.0f};
        bool        use_rope{false};
    };

    explicit MultiHeadAttention(Config cfg);
    ~MultiHeadAttention();

    MultiHeadAttention(const MultiHeadAttention&)            = delete;
    MultiHeadAttention& operator=(const MultiHeadAttention&) = delete;
    MultiHeadAttention(MultiHeadAttention&&) noexcept;
    MultiHeadAttention& operator=(MultiHeadAttention&&) noexcept;

    /// @param query   [batch, seq_q, embed_dim]
    /// @param key     [batch, seq_k, embed_dim]
    /// @param value   [batch, seq_k, embed_dim]
    /// @param mask    optional boolean mask [batch, 1, seq_q, seq_k]
    [[nodiscard]] core::Tensor forward(const core::Tensor&             query,
                                       const core::Tensor&             key,
                                       const core::Tensor&             value,
                                       std::optional<core::Tensor>     mask = std::nullopt) const;

    [[nodiscard]] const Config& config() const noexcept;

private:
    struct Impl;
    Impl* impl_{nullptr};
};

} // namespace mtl::nn
