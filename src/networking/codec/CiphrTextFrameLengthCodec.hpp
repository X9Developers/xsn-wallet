#ifndef CIPHRTEXTFRAMELENGTHCODEC_HPP
#define CIPHRTEXTFRAMELENGTHCODEC_HPP

#include "FrameLengthCodec.hpp"

class CiphrTextFrameLengthCodec : public FrameLengthCodec
{
public:
    CiphrTextFrameLengthCodec() = default;

    QByteArray encodeLength(int length);
    int decodeLength(const QByteArray &data, int *offset);
};

#endif // CIPHRTEXTFRAMELENGTHCODEC_HPP
