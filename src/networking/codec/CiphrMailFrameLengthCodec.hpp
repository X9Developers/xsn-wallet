#ifndef CIPHRMAILFRAMELENGTHCODEC_HPP
#define CIPHRMAILFRAMELENGTHCODEC_HPP

#include "FrameLengthCodec.hpp"

class CiphrMailFrameLengthCodec : public FrameLengthCodec
{
public:
    CiphrMailFrameLengthCodec() = default;

    QByteArray encodeLength(int length);
    int decodeLength(const QByteArray &data, int *offset);
};

#endif // CIPHRMAILFRAMELENGTHCODEC_HPP
