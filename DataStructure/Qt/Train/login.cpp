#include "login.h"
#include "ui_login.h"
#include "../../src/Exceptions.hpp"
#include <QString>
#include <iostream>
#include <QMessageBox>
//#include ""

//class User;
//sjtu::User user;

void Login::set_user(shared_ptr<User> _user) {
    user = _user;
}

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginBtn_clicked()
{
    string user_id = (ui -> usrLineEdit -> text()).toStdString();
    string user_pwd = (ui -> pwdLineEdit -> text()).toStdString();
    try {
        user -> login(user_id, user_pwd);
    }
    catch (const sjtu::Exception &exp) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exp.detail));
        return;
    }
    QMessageBox::information(nullptr, "Notice", "登录成功");
}

void Login::on_logoutBtn_clicked()
{
    close();
}
