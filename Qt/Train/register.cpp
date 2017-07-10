#include "register.h"
#include "ui_register.h"
#include <QString>
#include <iostream>
#include <QMessageBox>
#include "../../src/Exceptions.hpp"
#include <string>

using std::string;

void Register::set_user(shared_ptr<User> _user) {
    user = _user;
}

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}
/*

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
}*/

void Register::on_quitBtn_clicked()
{
    close();
}

void Register::on_registerBtn_clicked()
{
    string user_name = (ui -> usrLineEdit -> text()).toStdString();
    string user_pwd = (ui -> pwdLineEdit -> text()).toStdString();
    string user_pwd2 = (ui -> pwd2LineEdit -> text()).toStdString();
    string code = (ui -> codeLineEdit -> text()).toStdString();
    string user_id;
    if (ui -> checkBox -> isChecked()) {
        try {
            user_id = user -> create_admin(user_name, user_pwd, user_pwd2, code);
        }
        catch (const sjtu::Exception &exp) {
            QMessageBox::information(nullptr, "Warning", QString::fromStdString(exp.detail));
            return;
        }
        //QMessageBox::information(nullptr, "Notice", "管理员注册");

    } else {
        try {
            user_id = user -> create_user(user_name, user_pwd, user_pwd2);
        }
        catch (const sjtu::Exception &exp) {
            QMessageBox::information(nullptr, "Warning", QString::fromStdString(exp.detail));
            return;
        }
       // QMessageBox::information(nullptr, "Notice", "普通用户注册");
    }
    QMessageBox::information(nullptr, "Notice", QString::fromStdString("注册成功！\n ID为" + user_id));
}
