#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>

//roma
//Vodka

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graph.setQWidget(ui->plot); //grafik

    //Получим список доступных в системе сом портов при помощи QSerialPortInfo
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort port;
        port.setPort(info);
        if(port.open(QIODevice::ReadWrite))
        {
            ui->comboBox->addItem(info.portName(), 0);
            ui->comboBox_2->addItem(info.portName(), 0);
            qDebug() <<  info.portName();
        }
        else
            qDebug() <<"loh";
    }


    timer = new QTimer(this);


//    connect(&threadDeltaL, &QThread::started, &portDeltaL, &SerialPorts::run);//ne uverena, nuzny li eti konnekty
//    connect(&threadKraft, &QThread::started, &portKraft, &SerialPorts::run);


    connect(timer, &QTimer::timeout, &portKraft, &SerialPorts::run);
    connect(timer, &QTimer::timeout, &portDeltaL, &SerialPorts::run);

    connect(&portKraft, &SerialPorts::recievedData, this, &MainWindow::KraftRecieve);
    connect(&portDeltaL, &SerialPorts::recievedData, this, &MainWindow::DeltaLRecieve);

    connect(&thread, SIGNAL(finished()), &portKraft, SLOT(deleteLater()));
    connect(&thread,SIGNAL(finished()), &portDeltaL, SLOT(deleteLater()));


    portKraft.moveToThread(&thread);
    portDeltaL.moveToThread(&thread);

//    QTime t;
//    qDebug() <<t.currentTime();




    connect(ui->radioButton, SIGNAL(pressed()), this, SLOT(circle()));
    connect(ui->radioButton_2, SIGNAL(pressed()), this, SLOT(rect()));



}

MainWindow::~MainWindow()
{
    delete ui;

    thread.quit();
    thread.wait();
}




void MainWindow::KraftRecieve(QString ba1)
{
    ui->lineEdit->setText(ba1);

    if(ba1!="")
        kraft.push_back(ba1.toFloat());

    time.push_back(qtime.elapsed());//vremia v fail


//    if(kraft.size()==deltaL.size())     //chto-to pridumat
//        graph.printPlot(deltaL, kraft);

//    int t=kraft.size()-deltaL.size();
//        if(t!=0)
//            {

//                if(t>0)
//                    for(int i=0; i<t; ++i)
//                        kraft.erase(kraft.end()-1);
//                else
//                    for(int i=0; i>t; --i)
//                        deltaL.erase(deltaL.end()-1);

//                 graph.printPlot(deltaL, kraft);
//            }
//        else
//            graph.printPlot(deltaL, kraft);
}

void MainWindow::DeltaLRecieve(QString ba1)
{
    ui->lineEdit_2->setText(ba1);
    if(ba1!="")
        deltaL.push_back(ba1.toFloat());
//qDebug()<<kraft.size()<<deltaL.size();

    if(kraft.size()==deltaL.size())     //chto-to pridumat
        graph.printPlot(deltaL, kraft);
    else
    {
        int t=kraft.size()-deltaL.size();
        if(t!=0)
        {

            if(t>0)
                for(int i=0; i<t; ++i)
                    kraft.erase(kraft.end()-1);
            else
                for(int i=0; i>t; --i)
                    deltaL.erase(deltaL.end()-1);

             graph.printPlot(deltaL, kraft);
        }
        else
            graph.printPlot(deltaL, kraft);
    }

}

void MainWindow::on_pushButton_clicked()
{
    portKraft.addPort(ui->comboBox->currentText());//ne aktualno //peredelat, chtob s izmeneniem v combobox menialsia port
    portDeltaL.addPort(ui->comboBox_2->currentText());//^

    portKraft.portOpen();
    portDeltaL.portOpen();

    thread.start();

    timer->start(100);
    qtime.start();

}

void MainWindow::on_pushButton_2_clicked()
{
    portKraft.portClose();
    portDeltaL.portClose();

    thread.terminate();

}



void MainWindow::on_pushButton_3_clicked()
{
    QString fileName=QFileDialog::getSaveFileName(this);
    QFile file(fileName);
       if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
           return;

       QTextStream out(&file);
       out <<  "kraft\t"<< "deltaL\t" << "time"<<"\n";

   for (int i = 0; i < kraft.size(); ++i)//sdelat proverku na size dvuch massivov
   {
       out <<kraft.at(i)<<"  |  "<<deltaL.at(i)<< "  |  "<<time.at(i)<<"\n";
   }
   file.close();

}

void MainWindow::on_pushButton_4_clicked()
{
    portKraft.writeData("ZERO\r\n");
    portDeltaL.writeData("ZERO\r\n");
}

void MainWindow::rect()
{
    qDebug()<<666;

    QList<QString> rect={"rect1", "rect2", "rect3", "pirozman"};
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(rect);
}

void MainWindow::circle()
{
    QList <QString> circle={"circle1", "circle2"};
    ui->comboBox_3->clear();
    ui->comboBox_3->addItems(circle);

}
