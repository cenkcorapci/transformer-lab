#include <mtl/ops/softmax.hpp>
#include <mtl/utils/error.hpp>

#include <gtest/gtest.h>

namespace {

TEST(SoftmaxTest, ThrowsNotImplemented) {
    mtl::core::Tensor input({4}, mtl::core::DataType::Float32);
    mtl::core::Tensor output({4}, mtl::core::DataType::Float32);

    // Softmax is not yet implemented — verify the stub throws correctly.
    EXPECT_THROW(mtl::ops::softmax(input, output), mtl::utils::NotImplemented);
}

TEST(SoftmaxTest, InplaceThrowsNotImplemented) {
    mtl::core::Tensor t({4}, mtl::core::DataType::Float32);
    EXPECT_THROW(mtl::ops::softmax_inplace(t), mtl::utils::NotImplemented);
}

TEST(LogSoftmaxTest, ThrowsNotImplemented) {
    mtl::core::Tensor input({8}, mtl::core::DataType::Float32);
    mtl::core::Tensor output({8}, mtl::core::DataType::Float32);
    EXPECT_THROW(mtl::ops::log_softmax(input, output), mtl::utils::NotImplemented);
}

} // namespace
