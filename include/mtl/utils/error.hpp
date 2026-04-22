#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

namespace mtl::utils {

/// Base exception for all metal-transformer-lab errors.
class MtlError : public std::runtime_error {
public:
    explicit MtlError(std::string_view msg) : std::runtime_error(std::string(msg)) {}
};

/// Thrown when a Metal API call returns an unexpected error.
class MetalError : public MtlError {
public:
    explicit MetalError(std::string_view msg) : MtlError(msg) {}
};

/// Thrown when tensor shapes are incompatible for an operation.
class ShapeError : public MtlError {
public:
    explicit ShapeError(std::string_view msg) : MtlError(msg) {}
};

/// Thrown when an invalid argument is passed to a function.
class InvalidArgument : public MtlError {
public:
    explicit InvalidArgument(std::string_view msg) : MtlError(msg) {}
};

/// Thrown when a feature is not yet implemented (stub placeholder).
class NotImplemented : public MtlError {
public:
    explicit NotImplemented(std::string_view feature)
        : MtlError(std::string("Not implemented: ") + std::string(feature)) {}
};

/// Asserts a condition and throws InvalidArgument if false.
inline void check(bool condition, std::string_view msg) {
    if (!condition) {
        throw InvalidArgument(msg);
    }
}

} // namespace mtl::utils
