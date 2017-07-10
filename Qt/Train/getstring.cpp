#include "getstring.h"
#include "ui_getstring.h"

GetString::GetString(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetString)
{
    ui->setupUi(this);
}

GetString::~GetString()
{
    delete ui;
}

void GetString::give_information(const string &obj) {
    ui -> label -> setText("请输入" + QString::fromStdString(obj));
}

void GetString::on_quitBtn_clicked()
{
    close();
}

void GetString::on_enterBtn_clicked()
{
    send_string(ui -> stringEdit -> text().toStdString());

    //emit queried(ui -> stringEdit -> text().toStdString());
    //send_int(ui -> numEdit -> text().toInt());
    close();
}
