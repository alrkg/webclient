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
    QObject::connect(&tcpSocket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&tcpSocket_, &QIODevice::readyRead, this, &Widget::doReadyRead);

    QObject::connect(&sslSocket_, &QAbstractSocket::connected, this, &Widget::doConnected);
    QObject::connect(&sslSocket_, &QAbstractSocket::disconnected, this, &Widget::doDisconnected);
    QObject::connect(&sslSocket_, &QIODevice::readyRead, this, &Widget::doReadyRead);
}

Widget::~Widget()
{
    delete ui;
}

ushort Widget::checkProtocol(){
    if (ui->rbSsl->isChecked()) return 443;
    return 80;
}

void Widget::doConnected(){
    QString msg;
    if (checkProtocol() == 80)
        msg = "Connected " + tcpSocket_.peerAddress().toString() + " using TCP\n";
    else
        msg = "Connected " + sslSocket_.peerAddress().toString() + " using SSL\n";
    ui->pteMessage->insertPlainText(msg);
}

void Widget::doDisconnected(){
    QString msg = "Disconnected\n";
    ui->pteMessage->insertPlainText(msg);
}

void Widget::doReadyRead(){
    QByteArray ba;
    if (checkProtocol() == 80)
        ba = tcpSocket_.readAll();
    else
        ba = sslSocket_.readAll();
    ui->pteMessage->insertPlainText(ba);
}

void Widget::on_pbConnect_clicked()
{
    if(checkProtocol() == 80)
        tcpSocket_.connectToHost(ui->leHost->text(), checkProtocol());
    else
        sslSocket_.connectToHostEncrypted(ui->leHost->text(), checkProtocol());
}


void Widget::on_pbDisconnect_clicked()
{
    if (checkProtocol() == 80)
        tcpSocket_.disconnectFromHost();
    else
        sslSocket_.disconnectFromHost();
}


void Widget::on_pbSend_clicked()
{
    if (checkProtocol() == 80)
        tcpSocket_.write(ui->pteSend->toPlainText().toUtf8());
    else
        sslSocket_.write(ui->pteSend->toPlainText().toUtf8());
}


void Widget::on_pbClear_clicked()
{
    ui->pteMessage->clear();
}

