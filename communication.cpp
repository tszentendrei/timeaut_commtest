#include "communication.h"

Communication::Communication(QObject *parent) : QObject(parent)
{
    _msg_len = 0;

    _ser.setPortName(QString("COM12"));
    _ser.setBaudRate(115200);

}

void Communication::connect()
{
    _ser.open(QIODevice::ReadWrite);

    _send_stream = std::make_unique<QDataStream>(&_ser);
    _send_stream->setByteOrder(QDataStream::BigEndian);

    _recv_stream = std::make_unique<QDataStream>(&_ser);
    _recv_stream->setByteOrder(QDataStream::LittleEndian);

    QObject::connect(&_ser, SIGNAL(readyRead()), this, SLOT(processData()));
}

void Communication::doComm()
{
    QDataStream& stream = *_send_stream;

    stream << "DATAREQ\r\n";
    _ser.flush();
}

void Communication::processData()
{
    QDataStream &stream = *_recv_stream;

    if(_msg_len == 0)
    {
        if(_ser.bytesAvailable() < sizeof(quint32))
            return;
        stream >> _msg_len;
    }

    if(_ser.bytesAvailable() < _msg_len)
        return;

    emit msgReady(stream);
}
