#include <mtl/nn/attention.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::nn {

struct MultiHeadAttention::Impl {
    Config cfg;
};

MultiHeadAttention::MultiHeadAttention(Config cfg)
    : impl_(new Impl{std::move(cfg)}) {}

MultiHeadAttention::~MultiHeadAttention() {
    delete impl_;
}

MultiHeadAttention::MultiHeadAttention(MultiHeadAttention&& other) noexcept
    : impl_(other.impl_) {
    other.impl_ = nullptr;
}

MultiHeadAttention& MultiHeadAttention::operator=(MultiHeadAttention&& other) noexcept {
    if (this != &other) {
        delete impl_;
        impl_       = other.impl_;
        other.impl_ = nullptr;
    }
    return *this;
}

core::Tensor MultiHeadAttention::forward(const core::Tensor& /*query*/,
                                         const core::Tensor& /*key*/,
                                         const core::Tensor& /*value*/,
                                         std::optional<core::Tensor> /*mask*/) const {
    // TODO: implement scaled dot-product attention:
    //   1. Project Q, K, V via Linear layers
    //   2. Split into num_heads
    //   3. Compute attn = softmax(Q @ K^T / sqrt(head_dim))
    //   4. Output = attn @ V
    //   5. Merge heads and project
    throw utils::NotImplemented("MultiHeadAttention::forward");
}

const MultiHeadAttention::Config& MultiHeadAttention::config() const noexcept {
    return impl_->cfg;
}

} // namespace mtl::nn
