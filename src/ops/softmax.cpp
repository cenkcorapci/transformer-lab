#include <mtl/ops/softmax.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::ops {

void softmax(const core::Tensor& /*input*/, core::Tensor& /*output*/, int /*axis*/) {
    // TODO: implement numerically-stable softmax on Metal (shaders/softmax.metal)
    // Algorithm:
    //   1. find max along axis
    //   2. subtract max and exponentiate
    //   3. divide by sum
    throw utils::NotImplemented("ops::softmax");
}

void softmax_inplace(core::Tensor& tensor, int axis) {
    softmax(tensor, tensor, axis);
}

void log_softmax(const core::Tensor& /*input*/, core::Tensor& /*output*/, int /*axis*/) {
    // TODO: implement log-softmax
    throw utils::NotImplemented("ops::log_softmax");
}

} // namespace mtl::ops
