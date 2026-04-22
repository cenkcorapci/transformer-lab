#include <mtl/nn/linear.hpp>
#include <mtl/utils/error.hpp>

#include <utility>

namespace mtl::nn {

struct Linear::Impl {
    std::size_t in_features;
    std::size_t out_features;
    core::Tensor weight;
    core::Tensor* bias_ptr{nullptr};
    core::Tensor bias_storage;
};

Linear::Linear(std::size_t in_features, std::size_t out_features, bool use_bias)
    : impl_(new Impl{
          in_features,
          out_features,
          core::Tensor({out_features, in_features}, core::DataType::Float32),
          nullptr,
          {}}) {
    if (use_bias) {
        impl_->bias_storage = core::Tensor({out_features}, core::DataType::Float32);
        impl_->bias_ptr     = &impl_->bias_storage;
    }
    impl_->weight.fill_zeros();
    if (impl_->bias_ptr) {
        impl_->bias_ptr->fill_zeros();
    }
}

Linear::~Linear() {
    delete impl_;
}

Linear::Linear(Linear&& other) noexcept : impl_(other.impl_) {
    other.impl_ = nullptr;
}

Linear& Linear::operator=(Linear&& other) noexcept {
    if (this != &other) {
        delete impl_;
        impl_       = other.impl_;
        other.impl_ = nullptr;
    }
    return *this;
}

core::Tensor Linear::forward(const core::Tensor& /*input*/) const {
    // TODO: dispatch to mtl::ops::matmul(input, weight^T) and add bias
    throw utils::NotImplemented("Linear::forward");
}

core::Tensor& Linear::weight() noexcept {
    return impl_->weight;
}

const core::Tensor& Linear::weight() const noexcept {
    return impl_->weight;
}

core::Tensor* Linear::bias() noexcept {
    return impl_->bias_ptr;
}

const core::Tensor* Linear::bias() const noexcept {
    return impl_->bias_ptr;
}

std::size_t Linear::in_features() const noexcept {
    return impl_->in_features;
}

std::size_t Linear::out_features() const noexcept {
    return impl_->out_features;
}

} // namespace mtl::nn
