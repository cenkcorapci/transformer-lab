#include <mtl/ops/activation.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::ops {

void gelu(const core::Tensor& /*input*/, core::Tensor& /*output*/) {
    // TODO: implement GELU Metal kernel
    throw utils::NotImplemented("ops::gelu");
}

void gelu_inplace(core::Tensor& tensor) {
    gelu(tensor, tensor);
}

void silu(const core::Tensor& /*input*/, core::Tensor& /*output*/) {
    // TODO: implement SiLU Metal kernel
    throw utils::NotImplemented("ops::silu");
}

void silu_inplace(core::Tensor& tensor) {
    silu(tensor, tensor);
}

void relu(const core::Tensor& /*input*/, core::Tensor& /*output*/) {
    // TODO: implement ReLU Metal kernel
    throw utils::NotImplemented("ops::relu");
}

void relu_inplace(core::Tensor& tensor) {
    relu(tensor, tensor);
}

} // namespace mtl::ops
