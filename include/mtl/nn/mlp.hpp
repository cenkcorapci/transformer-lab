#pragma once

#include <mtl/core/tensor.hpp>

#include <cstddef>

namespace mtl::nn {

/// Feed-Forward / MLP sub-block.
///
/// Standard transformer FFN:  FFN(x) = activation(x @ W1^T + b1) @ W2^T + b2
///
/// TODO: implement SwiGLU variant used in LLaMA:
///   FFN_SwiGLU(x) = (SiLU(x @ W_gate^T) * (x @ W_up^T)) @ W_down^T
class MLP {
public:
    enum class ActivationKind { GELU, SiLU, ReLU };

    struct Config {
        std::size_t    in_features{512};
        std::size_t    hidden_features{2048};
        ActivationKind activation{ActivationKind::GELU};
        bool           use_bias{true};
        bool           gated{false}; ///< if true, use gated variant (SwiGLU)
    };

    explicit MLP(Config cfg);
    ~MLP();

    MLP(const MLP&)            = delete;
    MLP& operator=(const MLP&) = delete;
    MLP(MLP&&) noexcept;
    MLP& operator=(MLP&&) noexcept;

    /// @param input  [batch, seq, in_features]
    /// @returns      [batch, seq, in_features]
    [[nodiscard]] core::Tensor forward(const core::Tensor& input) const;

    [[nodiscard]] const Config& config() const noexcept;

private:
    struct Impl;
    Impl* impl_{nullptr};
};

} // namespace mtl::nn
