/**
 * @file
 * @brief     This file contains helper functions for defining nonpb's structs.
 */
#ifndef DECODERS_HPP
#define DECODERS_HPP

#include <string>
#include <vector>
#include <cstdint>

#include <optional/Optional.hpp>

#include "pb_decode.h"

namespace common
{
namespace nanopb
{
namespace decoders
{
/**
 * @brief           nanopb compatible function for deserializing std::string
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an std::string*
 * @return          true on success, false on error (See stream->errmsg for error code)
*/
bool DecodeStr(pb_istream_t *stream, const pb_field_t *field, void **arg);

/**
 * @brief           nanopb compatible function for deserializing std::vector<uint8_t>
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an std::vector<uint8_t>*
 * @return          true on success, false on error (See stream->errmsg for error code)
*/
bool DecodeBuffer(pb_istream_t *stream, const pb_field_t *field, void **arg);

/**
 * @brief           nanopb compatible function for deserializing std::vector<T>
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an std::vector<T>*
 * @return          true on success, false on error (See stream->errmsg for error code)
*/
template <typename T, typename NanoBuffT, pb_msgdesc_t const * Fields>
bool DecodeRepeated(pb_istream_t *stream, const pb_field_t *, void **arg)
{
    auto arr_p = reinterpret_cast<std::vector<T>**>(arg);
    if ((nullptr == arr_p) || (nullptr == arr_p[0]))
    {
        return false;
    }

    auto& arr = **arr_p;
    arr.emplace_back();
    auto& newItem = arr.back();

    return pb_decode(stream, Fields, reinterpret_cast<NanoBuffT*>(&newItem));
}
}  // namespace decoders

/**
 * @brief		Creates a pb_callback_t struct for deserializing an std::string
 * @param str	String to deserialize
 * @return		nanopb's pb_callback_t
*/
pb_callback_t CreateDecodingCallback(std::string& str);

/**
 * @brief		Creates a pb_callback_t struct for deserializing an std::vector<uint8_t>
 * @param str	Buffer to deserialize
 * @return		nanopb's pb_callback_t
*/
pb_callback_t CreateDecodingCallback(std::vector<uint8_t>& buffer);

/**
 * @brief		Creates a pb_callback_t struct for deserializing an std::vector<T>
 * @param str	Buffer to deserialize
 * @return		nanopb's pb_callback_t
*/
template <typename NanoBuffT, pb_msgdesc_t const * Fields, typename T>
pb_callback_t CreateDecodingCallback(std::vector<T>& buffer)
{
    return
    {
        { &decoders::DecodeRepeated<T, NanoBuffT, Fields> },
        static_cast<void*>(&buffer)
    };
}

/**
 * @brief				Serialize a nanopb struct
 * @tparam Fields		Nanopb structs fields definition 
 * @tparam NanopbStruct Nanopb struct type
 * @param message		nanopb message to deserialize
 * @return				returns empty optional on failure; A valid ByteVector optional on success
*/
template <pb_msgdesc_t const * Fields, typename NanopbStruct>
bool DecodeNanoPb(NanopbStruct& message, std::vector<uint8_t> const & buffer)
{
    pb_istream_t pbInStream =
    {
        [](pb_istream_t *self, uint8_t* buf, size_t count)
        {
            const auto writeCount = count <= self->bytes_left ? count : self->bytes_left;
            if (buf != nullptr) memcpy(buf, self->state, writeCount);
            
            reinterpret_cast<uint8_t*&>(self->state) += writeCount;
            return writeCount == count;
        },
        const_cast<uint8_t*>(buffer.data()),
        buffer.size(),
        nullptr
    };

    return pb_decode(&pbInStream, Fields, &message);
}

} // namespace nanopb
} // namespace common

#endif // DECODERS_HPP
