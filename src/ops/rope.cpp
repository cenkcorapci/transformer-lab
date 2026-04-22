#include <mtl/ops/rope.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::ops {

void rope(core::Tensor& /*q*/,
          core::Tensor& /*k*/,
          const core::Tensor& /*pos*/,
          float /*base*/) {
    // TODO: implement Rotary Position Embedding Metal kernel (shaders/rope.metal)
    // Algorithm:
    //   For each (batch, seq, head, i):
    //     theta_i = pos / base^(2i / head_dim)
    //     q'[..., 2i]   = q[..., 2i] * cos(theta_i) - q[..., 2i+1] * sin(theta_i)
    //     q'[..., 2i+1] = q[..., 2i] * sin(theta_i) + q[..., 2i+1] * cos(theta_i)
    throw utils::NotImplemented("ops::rope");
}

} // namespace mtl::ops
