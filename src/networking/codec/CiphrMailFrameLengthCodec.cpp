#include "CiphrMailFrameLengthCodec.hpp"

#include <QtEndian>

QByteArray CiphrMailFrameLengthCodec::encodeLength(int length)
{
    Q_ASSERT(length > 0);

    QByteArray buffer(sizeof(int), Qt::Uninitialized);
    qToBigEndian(length, (uchar*)buffer.data());

    return buffer;
}

int CiphrMailFrameLengthCodec::decodeLength(const QByteArray &data, int *offset)
{
    Q_ASSERT(offset != nullptr);

    const int lengthSize = sizeof(int);
    if (data.length() < lengthSize) {
        return -1;
    }

    *offset = lengthSize;
    return qFromBigEndian<int>((uchar*)data.data());
}
