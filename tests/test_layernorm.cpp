#include <mtl/ops/layernorm.hpp>
#include <mtl/utils/error.hpp>

#include <gtest/gtest.h>

namespace {

TEST(LayerNormTest, ThrowsNotImplemented) {
    const std::size_t hidden = 16;
    mtl::core::Tensor input ({hidden}, mtl::core::DataType::Float32);
    mtl::core::Tensor weight({hidden}, mtl::core::DataType::Float32);
    mtl::core::Tensor bias  ({hidden}, mtl::core::DataType::Float32);
    mtl::core::Tensor output({hidden}, mtl::core::DataType::Float32);

    EXPECT_THROW(mtl::ops::layernorm(input, weight, bias, output),
                 mtl::utils::NotImplemented);
}

TEST(RMSNormTest, ThrowsNotImplemented) {
    const std::size_t hidden = 16;
    mtl::core::Tensor input ({hidden}, mtl::core::DataType::Float32);
    mtl::core::Tensor weight({hidden}, mtl::core::DataType::Float32);
    mtl::core::Tensor output({hidden}, mtl::core::DataType::Float32);

    EXPECT_THROW(mtl::ops::rmsnorm(input, weight, output),
                 mtl::utils::NotImplemented);
}

} // namespace
