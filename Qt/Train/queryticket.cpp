#include "queryticket.h"
#include "ui_queryticket.h"
#include "../../src/Exceptions.hpp"
#include <QString>
#include <iostream>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>

void QueryTicket::set_user(shared_ptr<User> _user) {
    user = _user;
}

QueryTicket::QueryTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryTicket)
{
    ui->setupUi(this);
}

QueryTicket::~QueryTicket()
{
    delete ui;
}

void QueryTicket::on_quitBtn_clicked()
{
    close();
}

void QueryTicket::on_queryBtn_clicked()
{
    string train_id = (ui -> trainEdit -> text()).toStdString();
    string start_lo = (ui -> placeEdit1 -> text()).toStdString();
    string finish_lo = (ui -> placeEdit2 -> text()).toStdString();
    string level = (ui -> levelEdit -> text()).toStdString();
    int number = (ui -> numEdit -> text()).toInt();
    string date1 = (ui -> dateEdit1 -> dateTime()).toString("yyyy-MM-dd,hh:mm").toStdString();
    string date2 = (ui -> dateEdit2 -> dateTime()).toString("yyyy-MM-dd,hh:mm").toStdString();
    send_information(train_id, start_lo, finish_lo, date1, date2, level, number);
    //send_information(date1);
    close();
}
