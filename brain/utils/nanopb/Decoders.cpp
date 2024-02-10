#include "Decoders.hpp"

using namespace common::nanopb;

pb_callback_t common::nanopb::CreateDecodingCallback(std::string& str)
{
    return
    {
        { decoders::DecodeStr },
        static_cast<void*>(&str)
    };
}

pb_callback_t common::nanopb::CreateDecodingCallback(std::vector<uint8_t>& buffer)
{
    return
    {
        { decoders::DecodeBuffer },
        static_cast<void*>(&buffer)
    };
}

bool decoders::DecodeStr(pb_istream_t *stream, const pb_field_t *, void **arg)
{
    auto str_p = reinterpret_cast<std::string**>(arg);
    if ((nullptr == str_p) || ( nullptr == str_p[0]))
    {
        return false;
    }

    auto& str = **str_p;
    str.resize(stream->bytes_left);
    return pb_read(stream, reinterpret_cast<pb_byte_t*>(const_cast<char*>(str.c_str())), stream->bytes_left);
}

bool decoders::DecodeBuffer(pb_istream_t *stream, const pb_field_t *, void **arg)
{
    auto buff_p = reinterpret_cast<std::vector<uint8_t>**>(arg);
    if ((nullptr == buff_p) || (nullptr == buff_p[0]))
    {
        return false;
    }

    auto& buff = **buff_p;
    buff.resize(stream->bytes_left);
    return pb_read(stream, buff.data(), stream->bytes_left);
}