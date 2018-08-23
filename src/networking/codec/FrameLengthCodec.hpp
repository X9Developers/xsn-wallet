#ifndef FRAMELENGTHCODEC_HPP
#define FRAMELENGTHCODEC_HPP

#include <QByteArray>

/*
 * Push frame codec interface.
 */
class FrameLengthCodec
{
public:
    /*
     * Encodes the given length value to array of bytes.
     */
    virtual QByteArray encodeLength(int length) = 0;

    /*
     * Decodes the length from array of bytes.
     * If data is insufficient, returns -1 and `offset` is not modified.
     * If decode succeeded, returns length and updated `offset`.
     * `offset` designates the frame payload offset.
     */
    virtual int decodeLength(const QByteArray &data, int *offset) = 0;

protected:
    FrameLengthCodec() = default;
    virtual ~FrameLengthCodec() = default;
};

#endif // FRAMELENGTHCODEC_HPP
