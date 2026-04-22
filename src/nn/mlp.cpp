#include <mtl/nn/mlp.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::nn {

struct MLP::Impl {
    Config cfg;
};

MLP::MLP(Config cfg) : impl_(new Impl{std::move(cfg)}) {}

MLP::~MLP() {
    delete impl_;
}

MLP::MLP(MLP&& other) noexcept : impl_(other.impl_) {
    other.impl_ = nullptr;
}

MLP& MLP::operator=(MLP&& other) noexcept {
    if (this != &other) {
        delete impl_;
        impl_       = other.impl_;
        other.impl_ = nullptr;
    }
    return *this;
}

core::Tensor MLP::forward(const core::Tensor& /*input*/) const {
    // TODO: implement FFN forward:
    //   standard: activation(x @ W1^T + b1) @ W2^T + b2
    //   gated:    (SiLU(x @ W_gate^T) * (x @ W_up^T)) @ W_down^T
    throw utils::NotImplemented("MLP::forward");
}

const MLP::Config& MLP::config() const noexcept {
    return impl_->cfg;
}

} // namespace mtl::nn
