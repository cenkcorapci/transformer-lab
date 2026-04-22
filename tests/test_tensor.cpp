#include <mtl/core/tensor.hpp>
#include <mtl/core/types.hpp>
#include <mtl/utils/error.hpp>

#include <gtest/gtest.h>

#include <cstddef>
#include <vector>

namespace {

TEST(TensorTest, DefaultConstruction) {
    mtl::core::Tensor t;
    EXPECT_EQ(t.ndim(), 0u);
    EXPECT_EQ(t.numel(), 0u);
    EXPECT_EQ(t.nbytes(), 0u);
}

TEST(TensorTest, ShapeAndSize) {
    mtl::core::Tensor t({4, 8}, mtl::core::DataType::Float32);
    EXPECT_EQ(t.ndim(), 2u);
    EXPECT_EQ(t.numel(), 32u);
    EXPECT_EQ(t.nbytes(), 32u * sizeof(float));
    EXPECT_EQ(t.shape()[0], 4u);
    EXPECT_EQ(t.shape()[1], 8u);
}

TEST(TensorTest, FillZeros) {
    mtl::core::Tensor t({16}, mtl::core::DataType::Float32);
    t.fill_zeros();
    auto span = t.data_as<float>();
    for (auto v : span) {
        EXPECT_FLOAT_EQ(v, 0.0f);
    }
}

TEST(TensorTest, FillOnes) {
    mtl::core::Tensor t({8}, mtl::core::DataType::Float32);
    t.fill_ones();
    auto span = t.data_as<float>();
    for (auto v : span) {
        EXPECT_FLOAT_EQ(v, 1.0f);
    }
}

TEST(TensorTest, MoveSemantics) {
    mtl::core::Tensor a({4, 4}, mtl::core::DataType::Float32);
    a.fill_zeros();

    mtl::core::Tensor b = std::move(a);
    EXPECT_EQ(b.numel(), 16u);
}

TEST(TensorTest, IsContiguous) {
    mtl::core::Tensor t({2, 3, 4}, mtl::core::DataType::Float32);
    EXPECT_TRUE(t.is_contiguous());
}

TEST(TypesTest, DtypeSize) {
    EXPECT_EQ(mtl::core::dtype_size(mtl::core::DataType::Float32), 4u);
    EXPECT_EQ(mtl::core::dtype_size(mtl::core::DataType::Float16), 2u);
    EXPECT_EQ(mtl::core::dtype_size(mtl::core::DataType::Int8), 1u);
}

TEST(TypesTest, DtypeName) {
    EXPECT_EQ(mtl::core::dtype_name(mtl::core::DataType::Float32), "float32");
    EXPECT_EQ(mtl::core::dtype_name(mtl::core::DataType::BFloat16), "bfloat16");
}

} // namespace
