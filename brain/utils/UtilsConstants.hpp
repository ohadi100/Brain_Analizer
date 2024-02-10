#pragma once
#include "Constants.hpp"

#include <string>
using common::IDS_APPLICATION_NAME;
namespace brain
{
static constexpr uint64_t MEGA{1000000U};
static constexpr double   MEGA_D{1000000.0};
static constexpr uint64_t BITS_IN_BYTE{8U};
template <typename T>
constexpr T
BytesToBits(T BYTES)
{
    return ((BYTES)*BITS_IN_BYTE);
}
template <typename T>
constexpr T
BitsToBytes(T BITS)
{
    return ((BITS + BITS_IN_BYTE - 1) / BITS_IN_BYTE);
}
}  // namespace brain