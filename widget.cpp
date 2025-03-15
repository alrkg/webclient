#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->rbTcp->click();

    QObject::connect(&tcpSocket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&tcpSocket_, &QAbstractSocket::disconnected, this, [this]{doDisconnected(80);});
    QObject::connect(&tcpSocket_, &QIODevice::readyRead, this, &Widget::doReadyRead);

    QObject::connect(&sslSocket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&sslSocket_, &QAbstractSocket::disconnected, this, [this]{doDisconnected(443);});
    QObject::connect(&sslSocket_, &QIODevice::readyRead, this, &Widget::doReadyRead);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::doConnected(){
    if (protocol == 80)
        ui->lbTcp->setText("Connecting...");
    else
        ui->lbSsl->setText("Connecting...");
}

void Widget::doDisconnected(uint protocol){
    if (protocol == 80)
        ui->lbTcp->setText("Disconnected");
    else
        ui->lbSsl->setText("Disconnected");
}

void Widget::doReadyRead(){
    QByteArray ba;
    if (protocol == 80)
        ba = tcpSocket_.readAll();
    else
        ba = sslSocket_.readAll();
    ui->pteMessage->insertPlainText(ba);
}

void Widget::on_pbConnect_clicked()
{
    if(protocol == 80)
        tcpSocket_.connectToHost(ui->leHost->text(), protocol);
    else
        sslSocket_.connectToHostEncrypted(ui->leHost->text(), protocol);
}


void Widget::on_pbDisconnect_clicked()
{
    if (protocol == 80)
        tcpSocket_.disconnectFromHost();
    else
        sslSocket_.disconnectFromHost();
}


void Widget::on_pbSend_clicked()
{
    if (protocol == 80)
        tcpSocket_.write(ui->pteSend->toPlainText().toUtf8());
    else
        sslSocket_.write(ui->pteSend->toPlainText().toUtf8());
}


void Widget::on_pbClear_clicked()
{
    ui->pteMessage->clear();
}


void Widget::on_rbTcp_clicked()
{
    protocol = 80;
}


void Widget::on_rbSsl_clicked()
{
    protocol = 443;
}

