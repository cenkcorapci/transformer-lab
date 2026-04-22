#include <mtl/nn/transformer_block.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::nn {

struct TransformerBlock::Impl {
    Config cfg;
};

TransformerBlock::TransformerBlock(Config cfg)
    : impl_(new Impl{std::move(cfg)}) {}

TransformerBlock::~TransformerBlock() {
    delete impl_;
}

TransformerBlock::TransformerBlock(TransformerBlock&& other) noexcept
    : impl_(other.impl_) {
    other.impl_ = nullptr;
}

TransformerBlock& TransformerBlock::operator=(TransformerBlock&& other) noexcept {
    if (this != &other) {
        delete impl_;
        impl_       = other.impl_;
        other.impl_ = nullptr;
    }
    return *this;
}

core::Tensor TransformerBlock::forward(const core::Tensor& /*hidden_states*/,
                                       std::optional<core::Tensor> /*mask*/) const {
    // TODO: implement pre-norm transformer block:
    //   x = x + Attention(Norm(x))
    //   x = x + MLP(Norm(x))
    throw utils::NotImplemented("TransformerBlock::forward");
}

const TransformerBlock::Config& TransformerBlock::config() const noexcept {
    return impl_->cfg;
}

} // namespace mtl::nn
