#include "getnewpassword.h"
#include "ui_getnewpassword.h"

GetNewPassword::GetNewPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetNewPassword)
{
    ui->setupUi(this);
}

GetNewPassword::~GetNewPassword()
{
    delete ui;
}

void GetNewPassword::on_quitBtn_clicked()
{
    close();
}

void GetNewPassword::on_getpwd_clicked()
{
    send_string(ui -> oldPwdEdit -> text().toStdString(),
             ui -> pwd1Edit -> text().toStdString(),
             ui -> pwd2Edit -> text().toStdString());
    close();
}
