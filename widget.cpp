#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->rbTcp->click();
    protocol = TCP_PROTOCOL;

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


void Widget::doConnected() {
    if (protocol == TCP_PROTOCOL)
        ui->lbTcp->setText("Connected");
    else if (protocol == SSL_PROTOCOL)
        ui->lbSsl->setText("Connected");
}


void Widget::doDisconnected() {
    if (protocol == TCP_PROTOCOL)
       ui->lbTcp->setText("Disconnected");
    else if (protocol == SSL_PROTOCOL)
        ui->lbSsl->setText("Disconnected");
}


void Widget::doReadyRead() {
    QByteArray ba;
    if (protocol == TCP_PROTOCOL)
        ba = tcpSocket_.readAll();
    else if (protocol == SSL_PROTOCOL)
        ba = sslSocket_.readAll();
    ui->pteMessage->insertPlainText(ba);
}


void Widget::on_pbConnect_clicked() {
    if (protocol == TCP_PROTOCOL)
        tcpSocket_.connectToHost(ui->leHost->text(), protocol);
    else if (protocol == SSL_PROTOCOL)
        sslSocket_.connectToHostEncrypted(ui->leHost->text(), protocol);
}


void Widget::on_pbDisconnect_clicked() {
    if (protocol == TCP_PROTOCOL)
        tcpSocket_.disconnectFromHost();
    else if (protocol == SSL_PROTOCOL)
        sslSocket_.disconnectFromHost();
}


void Widget::on_pbSend_clicked() {
    ui->pteMessage->clear();

    if (protocol == TCP_PROTOCOL)
        tcpSocket_.write(ui->pteSend->toPlainText().toUtf8());
    else if (protocol == SSL_PROTOCOL)
        sslSocket_.write(ui->pteSend->toPlainText().toUtf8());
}


void Widget::on_pbClear_clicked() {
    ui->pteMessage->clear();
}
