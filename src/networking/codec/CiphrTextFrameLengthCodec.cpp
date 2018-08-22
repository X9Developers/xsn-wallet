#include "CiphrTextFrameLengthCodec.hpp"

#include <limits>

QByteArray CiphrTextFrameLengthCodec::encodeLength(int length)
{
    Q_ASSERT(length > 0);

    QByteArray buffer;
    while (true) {
        if ((length & ~0x7FL) == 0) {
            buffer.append(static_cast<char>(length));
            return buffer;
        } else {
            buffer.append((static_cast<char>(length) & 0x7F) | 0x80);
            length = length >> 7;
        }
    }
}

int CiphrTextFrameLengthCodec::decodeLength(const QByteArray &data, int *offset)
{
    Q_ASSERT(offset != nullptr);

    int index = 0;
    int shift = 0;
    qint64 result = 0;

    while (shift < 64 && index < data.length()) {
        char nextByte = data[index];
        result |= (qint64) (nextByte & 0x7F) << shift;
        if ((nextByte & 0x80) == 0) {
            *offset = index + 1;
            Q_ASSERT(result <= std::numeric_limits<int>::max());
            return (int)result;
        }
        shift += 7;
        index++;
    }

    return -1;
}
