#include <mtl/ops/layernorm.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::ops {

void layernorm(const core::Tensor& /*input*/,
               const core::Tensor& /*weight*/,
               const core::Tensor& /*bias*/,
               core::Tensor& /*output*/,
               float /*eps*/) {
    // TODO: implement fused LayerNorm Metal kernel (shaders/layernorm.metal)
    // Algorithm:
    //   mean = mean(x, axis=-1)
    //   var  = mean((x - mean)^2, axis=-1)
    //   y    = (x - mean) / sqrt(var + eps) * weight + bias
    throw utils::NotImplemented("ops::layernorm");
}

void rmsnorm(const core::Tensor& /*input*/,
             const core::Tensor& /*weight*/,
             core::Tensor& /*output*/,
             float /*eps*/) {
    // TODO: implement fused RMSNorm Metal kernel
    // Algorithm:
    //   rms = sqrt( mean(x^2) + eps )
    //   y   = x / rms * weight
    throw utils::NotImplemented("ops::rmsnorm");
}

} // namespace mtl::ops
