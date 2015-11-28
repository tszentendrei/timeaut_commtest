#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QBuffer>
#include <QDataStream>
#include <memory>

class Communication : public QObject
{
    Q_OBJECT

private:

    QSerialPort _ser;
    std::unique_ptr<QDataStream> _send_stream;
    std::unique_ptr<QDataStream> _recv_stream;
    quint32 _msg_len;

public:
    explicit Communication(QObject *parent = 0);
    void connect();

signals:
    void msgReady(QDataStream& msg);

public slots:
    void doComm();
    void processData();
};

#endif // COMMUNICATION_H
