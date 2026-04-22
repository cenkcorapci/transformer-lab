#include <mtl/nn/attention.hpp>
#include <mtl/utils/error.hpp>

#include <gtest/gtest.h>

namespace {

TEST(MultiHeadAttentionTest, Construction) {
    mtl::nn::MultiHeadAttention::Config cfg;
    cfg.embed_dim  = 128;
    cfg.num_heads  = 4;
    cfg.head_dim   = 32;
    cfg.is_causal  = true;

    mtl::nn::MultiHeadAttention attn(cfg);

    EXPECT_EQ(attn.config().embed_dim, 128u);
    EXPECT_EQ(attn.config().num_heads, 4u);
    EXPECT_TRUE(attn.config().is_causal);
}

TEST(MultiHeadAttentionTest, ForwardThrowsNotImplemented) {
    mtl::nn::MultiHeadAttention::Config cfg;
    cfg.embed_dim = 64;
    cfg.num_heads = 2;
    cfg.head_dim  = 32;

    mtl::nn::MultiHeadAttention attn(cfg);

    mtl::core::Tensor q({1, 8, 64}, mtl::core::DataType::Float32);
    mtl::core::Tensor k({1, 8, 64}, mtl::core::DataType::Float32);
    mtl::core::Tensor v({1, 8, 64}, mtl::core::DataType::Float32);

    EXPECT_THROW(attn.forward(q, k, v), mtl::utils::NotImplemented);
}

} // namespace
