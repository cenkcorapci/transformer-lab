#include <mtl/ops/matmul.hpp>
#include <mtl/utils/error.hpp>

namespace mtl::ops {

void matmul(const core::Tensor& /*A*/,
            const core::Tensor& /*B*/,
            core::Tensor& /*C*/,
            float /*alpha*/,
            float /*beta*/) {
    // TODO: validate A.shape[-1] == B.shape[-2]
    // TODO: dispatch to Metal compute kernel (shaders/matmul.metal)
    throw utils::NotImplemented("ops::matmul");
}

core::Tensor matmul(const core::Tensor& A, const core::Tensor& B) {
    const auto& sa = A.shape();
    const auto& sb = B.shape();
    utils::check(sa.size() >= 2 && sb.size() >= 2, "matmul: inputs must be at least 2-D");
    std::size_t M = sa[sa.size() - 2];
    std::size_t N = sb[sb.size() - 1];
    core::Tensor C({M, N}, A.dtype());
    matmul(A, B, C);
    return C;
}

} // namespace mtl::ops
