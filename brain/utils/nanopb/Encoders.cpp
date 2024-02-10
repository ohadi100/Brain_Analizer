#include <iostream>
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "brain/engines/security_events/ExternalUnsuccessfulConnectionsEntry.hpp"
#include "brain/engines/security_events/IpConnectionCounters.hpp"
#include "brain/engines/security_events/IpDroppedConnectionsEntry.hpp"
#include "brain/histograms/RateHistogram.hpp"
#include "brain/histograms/ScalarHistogram.hpp"
#include "brain/utils/CounterWithTs.hpp"

#include "Encoders.hpp" // implemented

using namespace common::nanopb;

bool
encoders::EncodeStr(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg)
{
    auto const& str_p = reinterpret_cast<std::string* const*>(arg);
    if ((nullptr == str_p) || (nullptr == str_p[0]))
    {
        return false;
    }

    if (!pb_encode_tag_for_field(stream, field))
    {
        return false;
    }

    auto const str = *str_p;
    return pb_encode_string(stream, reinterpret_cast<const uint8_t*>(str->c_str()), str->size());
}

bool
common::nanopb::encoders::EncodeSliteral(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg)
{
    auto const& str_p = reinterpret_cast<char* const*>(arg);
    if ((nullptr == str_p) || (nullptr == str_p[0]))
    {
        return false;
    }

    if (!pb_encode_tag_for_field(stream, field))
    {
        return false;
    }

    auto const str = *str_p;
    return pb_encode_string(stream, reinterpret_cast<const pb_byte_t*>(str), strlen(str));
}

bool
encoders::EncodeBuffer(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg)
{
    auto const& str_p = reinterpret_cast<std::vector<uint8_t>* const*>(arg);
    if ((nullptr == str_p) || (nullptr == str_p[0]))
    {
        return false;
    }

    if (!pb_encode_tag_for_field(stream, field))
    {
        return false;
    }

    auto const buff = *str_p;
    return pb_encode_string(stream, buff->data(), buff->size());
}

bool
encoders::EncodeArray(pb_ostream_t* const stream, pb_field_t const* const field, void* const* arg)
{
    auto const arr_p = reinterpret_cast<Array* const*>(arg);
    if ((nullptr == arr_p) || (nullptr == arr_p[0]))
    {
        return false;
    }
    auto const arr = *arr_p;
    if ((nullptr == arr->data) || (0 == arr->size))
    {
        return false;
    }

    if (!pb_encode_tag_for_field(stream, field))
    {
        return false;
    }

    return pb_encode_string(stream, arr->data, arr->size);
}

bool
encoders::EncodeRateHistogram(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg)
{
    auto const& binDataVec = **reinterpret_cast<brain::histogram::RateHistogram::BinDataVector* const*>(arg);
    for (auto const& binDataItem : binDataVec)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket bucket
            = com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_init_default;
        bucket.bin     = static_cast<float>(binDataItem.GetInterval());
        bucket.counter = static_cast<uint32_t>(binDataItem.GetHeight());

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields, &bucket)))
        {
            return false;
        }
    }
    return true;
}

bool
encoders::EncodeScalarHistogram(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg)
{
    auto const& binDataVec = **reinterpret_cast<brain::histogram::ScalarHistogram::BinDataVector* const*>(arg);

    for (auto const& binDataItem : binDataVec)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_Bucket bucket
            = com_vwg_connect_ids_idsperiodicreport_v1_Bucket_init_default;
        bucket.bin     = static_cast<uint32_t>(binDataItem.GetInterval());
        bucket.counter = static_cast<uint32_t>(binDataItem.GetHeight());

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_Bucket_fields, &bucket)))
        {
            return false;
        }
    }

    return true;
}

bool
encoders::EncodeScalarFloatingHistogram(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg)
{
    auto const& binDataVec = **reinterpret_cast<brain::histogram::ScalarHistogram::BinDataVector* const*>(arg);

    for (auto const& binDataItem : binDataVec)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket bucket
            = com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_init_default;
        bucket.bin     = static_cast<float>(binDataItem.GetInterval());
        bucket.counter = static_cast<uint32_t>(binDataItem.GetHeight());

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_FloatBucket_fields, &bucket)))
        {
            return false;
        }
    }

    return true;
}
bool
encoders::EncodeCounterData(pb_ostream_t* const stream, pb_field_t const* const fields, void* const* arg)
{
    auto const& countersTable
        = **reinterpret_cast<std::unordered_map<std::string, std::shared_ptr<brain::utils::CounterWithTs>>* const*>(
            arg);
    for (auto const& counterData : countersTable)
    {
        com_vwg_connect_ids_idsperiodicreport_v1_CounterData counter
            = com_vwg_connect_ids_idsperiodicreport_v1_CounterData_init_default;
        counter.key          = common::nanopb::CreateEncodingCallback(counterData.first);
        counter.counterValue = counterData.second->GetCounter();

        if ((!pb_encode_tag_for_field(stream, fields))
            || (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_CounterData_fields, &counter)))
        {
            return false;
        }
    }
    return true;
}

pb_callback_t
common::nanopb::CreateEncodingCallback(std::string const& str)
{
    pb_callback_t callback;

    callback.funcs.encode = encoders::EncodeStr;
    callback.arg = const_cast<void*>(static_cast<const void*>(&str));
 
    return callback;
}

pb_callback_t
common::nanopb::CreateEncodingLiteralStringCallback(const char* str)
{
    pb_callback_t callback;

    callback.funcs.encode = encoders::EncodeSliteral;
    callback.arg = const_cast<void*>(static_cast<const void*>(str));

    return callback;
}

pb_callback_t
common::nanopb::CreateEncodingCallback(std::vector<uint8_t> const& buffer)
{
    pb_callback_t callback;

    callback.funcs.encode = encoders::EncodeBuffer;
    callback.arg = const_cast<void*>(static_cast<const void*>(&buffer));

    return callback;
}

pb_callback_t
common::nanopb::CreateEncodingCallback(common::nanopb::Array const& arr)
{
    pb_callback_t callback;

    callback.funcs.encode = encoders::EncodeArray;
    callback.arg = const_cast<void*>(static_cast<const void*>(&arr));

    return callback;
}
