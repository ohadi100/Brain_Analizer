/**
 * @file
 * @brief     This file contains helper functions for defining nonpb's structs.
 */
#ifndef ENCODERS_HPP
#define ENCODERS_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <optional/Optional.hpp>

#include "pb_encode.h"

namespace common
{
namespace nanopb
{

struct Array {
    uint8_t const* data = nullptr;
    size_t size = 0;
};

namespace encoders
{
/**
 * @brief           nanopb compatible function for serializing std::string
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an std::string*
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeStr(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing c_strings
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to a c_string
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeSliteral(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing std::vector<uint8_t>
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an std::vector<uint8_t>*
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeBuffer(pb_ostream_t* const stream, const pb_field_t* const field, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing std::vector<uint8_t>
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an Array struct
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeArray(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing rate histogram
 * @param stream    nanopb stream
 * @param fields     nanopb field
 * @param arg       a pointer to a BinDataVector
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeRateHistogram(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing scalar histogram
 * @param stream    nanopb stream
 * @param fields     nanopb field
 * @param arg       a pointer to a BinDataVector
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeScalarHistogram(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing floating scalar histogram
 * @param stream    nanopb stream
 * @param fields     nanopb field
 * @param arg       a pointer to a BinDataVector
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeScalarFloatingHistogram(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing counter data
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to a BinDataVector
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
bool EncodeCounterData(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg);

/**
 * @brief           nanopb compatible function for serializing std::vector<T>
 * @param stream    nanopb stream
 * @param field     nanopb field
 * @param arg       a pointer to an std::vector<T>*
 * @return          true on success, false on error (See stream->errmsg for error code)
 */
template <typename T, typename NanoBuffT, pb_msgdesc_t const* Fields>
bool
EncodeRepeated(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg)
{
    auto arr_p = reinterpret_cast<std::vector<T> const* const*>(arg);
    if ((nullptr == arr_p) || (nullptr == arr_p[0]))
    {
        return false;
    }

    auto& arr = **arr_p;
    for (auto const& item : arr)
    {
        if (!pb_encode_tag_for_field(stream, fields) || !pb_encode_submessage(stream, Fields, reinterpret_cast<NanoBuffT const*>(&item)))
        {
            return false;
        }
    }

    return true;
}
}  // namespace encoders

/**
 * @brief		Creates a pb_callback_t struct for serializing an std::string
 * @param str	String to serialize
 * @return		nanopb's pb_callback_t
 */
pb_callback_t CreateEncodingCallback(std::string const& str);

/**
 * @brief		 Creates a pb_callback_t struct for serializing an std::vector<uint8_t>
 * @param buffer Buffer to serialize
 * @return		 nanopb's pb_callback_t
 */
pb_callback_t CreateEncodingCallback(std::vector<uint8_t> const& buffer);

/**
 * @brief		Creates a pb_callback_t struct for serializing an array of uint8_t with given size
 * @param arr	Array struct to serialize
 * @return		nanopb's pb_callback_t
 */
pb_callback_t CreateEncodingCallback(Array const& arr);

/**
 * @brief		Creates a pb_callback_t struct for serializing a c_string
 * @param str	String to serialize
 * @return		nanopb's pb_callback_t
 */
pb_callback_t CreateEncodingLiteralStringCallback(char const* str);

/**
 * @brief		Creates a pb_callback_t struct for serializing an std::vector<T>
 * @param str	Buffer to deserialize
 * @return		nanopb's pb_callback_t
 */
template <typename NanoBuffT, pb_msgdesc_t const* Fields, typename T>
pb_callback_t
CreateEncodingCallback(std::vector<T>& buffer)
{
    return {
        {reinterpret_cast<decltype(pb_callback_t::funcs.decode)>
         (& encoders::EncodeRepeated<T, NanoBuffT, Fields>)},  // Casting to a decode function because c++ doesn't allow
                                                             // the initialization of a speciefic enum variable

        static_cast<void*>(&buffer)};
}

/**
 * @brief				Serialize a nanopb struct
 * @tparam Fields		Nanopb structs fields definition
 * @tparam NanopbStruct Nanopb struct type
 * @param message		nanopb message to serizlize
 * @return				returns empty optional on failure; A valid ByteVector optional on success
 */
template <pb_msgdesc_t const* Fields, typename NanopbStruct>
cm::optional<std::vector<uint8_t>>
EncodeNanoPb(NanopbStruct const& message)
{
    std::vector<uint8_t> retVal;

    size_t estimatedSize           = 0;
    auto   getEstimatedSizeSuccess = pb_get_encoded_size(&estimatedSize, Fields, &message);
    if (!getEstimatedSizeSuccess)
    {
        return {};
    }
    retVal.reserve(estimatedSize);

    pb_ostream_t pbOutStream = {[](pb_ostream_t* self, const pb_byte_t* buf, size_t count) {
                                    auto& selfBuff = *static_cast<decltype(&retVal)>(self->state);
                                    selfBuff.insert(selfBuff.end(), buf, buf + count);
                                    return true;
                                },
                                &retVal,
                                SIZE_MAX,
                                0,
                                nullptr};

    auto const encode_successful = pb_encode(&pbOutStream, Fields, &message);
    return encode_successful ? cm::optional<std::vector<uint8_t>>(std::move(retVal))
                             : cm::optional<std::vector<uint8_t>>();
}

}  // namespace nanopb
}  // namespace common

#endif  // ENCODERS_HPP
