#pragma once

#include <cstdint>
#include <string_view>

namespace mtl::core {

/// Supported numeric data types.
enum class DataType : std::uint8_t {
    Float32 = 0,
    Float16,
    BFloat16, ///< M3+ only
    Int32,
    Int16,
    Int8,
    UInt8,
    Bool,
};

/// Returns the size in bytes of a single element of the given type.
[[nodiscard]] constexpr std::size_t dtype_size(DataType dt) noexcept {
    switch (dt) {
    case DataType::Float32: return 4;
    case DataType::Float16: return 2;
    case DataType::BFloat16: return 2;
    case DataType::Int32: return 4;
    case DataType::Int16: return 2;
    case DataType::Int8: return 1;
    case DataType::UInt8: return 1;
    case DataType::Bool: return 1;
    }
    return 0;
}

[[nodiscard]] constexpr std::string_view dtype_name(DataType dt) noexcept {
    switch (dt) {
    case DataType::Float32: return "float32";
    case DataType::Float16: return "float16";
    case DataType::BFloat16: return "bfloat16";
    case DataType::Int32: return "int32";
    case DataType::Int16: return "int16";
    case DataType::Int8: return "int8";
    case DataType::UInt8: return "uint8";
    case DataType::Bool: return "bool";
    }
    return "unknown";
}

} // namespace mtl::core
