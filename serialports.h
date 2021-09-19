#ifndef SERIAPORTS_H
#define SERIAPORTS_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>

class SerialPorts : public QObject
{
    Q_OBJECT

    //QVector<QSerialPort *> ports;
    QSerialPort * port;
   // QTimer* timer;

public:
    SerialPorts();
    ~SerialPorts();

    void addPort(QString);
    void portSettings();
    void changeName(QString);
    void portOpen();
    void portClose();
    void writeData(QByteArray);

public slots:
    void run(); // Метод с полезной нагрузкой, который может выполняться в цикле


signals:
    void recievedData(QString);

};

#endif // SERIAPORTS_H
