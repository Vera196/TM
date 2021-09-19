#include "serialports.h"
#include <QDebug>

SerialPorts::SerialPorts()
{
    //connect(port, SIGNAL(readyRead()), this, SLOT(run()));
    port = new QSerialPort(this);
   // timer = new QTimer(this);
    //connect(port, &QSerialPort::readyRead, this, &SerialPorts::run);
    //connect(timer, &QTimer::timeout, this, &SerialPorts::run);
}

SerialPorts::~SerialPorts()
{
    port->close();
}


void SerialPorts::addPort(QString name)
{

    port->setPortName(name);
    portSettings();
}

void SerialPorts::portSettings()
{
    port->setBaudRate(QSerialPort::Baud9600);
    port->setDataBits(QSerialPort::Data8);
    port->setParity(QSerialPort::NoParity);
    port->setStopBits(QSerialPort::OneStop);
    port->setFlowControl(QSerialPort::NoFlowControl);
}

void SerialPorts::changeName(QString name)
{
    port->setPortName(name);
}

void SerialPorts::portOpen()
{
    port->open(QIODevice::ReadWrite);
}

void SerialPorts::portClose()
{
    port->close();
}

void SerialPorts::writeData(QByteArray ba)
{
    port->write(ba);
}

void SerialPorts::run()
{
    QString ba1;

    ba1 = port->readAll();
//    if(ba1=="")
//        return;
    ba1=ba1.mid(1, 7);
    qDebug() <<ba1;

    emit recievedData(ba1);
}




