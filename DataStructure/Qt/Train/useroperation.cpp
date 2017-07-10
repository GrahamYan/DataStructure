#include "useroperation.h"
#include "ui_useroperation.h"

#include <QString>
#include <iostream>
#include <QMessageBox>
#include "../../src/Exceptions.hpp"
#include "getint.h"
#include "getnewpassword.h"
#include "getstring.h"
#include "plaintable.h"
#include "tickettable.h"
#include <string>

using std::string;

void UserOperation::set_user(shared_ptr<User> _user) {
    user = _user;
}

UserOperation::UserOperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserOperation)
{
    ui->setupUi(this);
}

UserOperation::~UserOperation()
{
    delete ui;
}

void UserOperation::set_number_with_user(int number)  {
//std::cout << "充值 " << number << std::endl;
    number_with_user = number;
}


void UserOperation::on_chargeButton_clicked()
{
    GetInt getint;
    //aaa.test();
    //aaa.set_my_bound(1);
    getint.set_bound(31415);

    number_with_user = -2147483648;
    QDialog::connect(&getint, &GetInt::queried, this, &UserOperation::set_number_with_user);
    try {
        getint.exec();
        if (number_with_user == -2147483648) {
            return;
        }
        user -> charge(number_with_user);
        if (number_with_user < 0 || number_with_user > 31415.926) {
            QMessageBox::information(nullptr, "Warning", "充值金额不合法！");
            return;
        }
        QMessageBox::information(nullptr, "Notice", "用户充值" +
                                 QString::number(number_with_user) +
                                 "成功，余额为" +
                                 QString::number(user -> query_money()));
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void UserOperation::set_string(const string &_s1, const string &_s2, const string &_s3) {
    s1 = _s1;
    s2 = _s2;
    s3 = _s3;
}

void UserOperation::on_pwdButton_clicked()
{
    GetNewPassword getstring;
    s1 = "";
    QDialog::connect(&getstring, &GetNewPassword::queried, this, &UserOperation::set_string);
    try {
        getstring.exec();
        if (s1 == "") {
            return;
        }
        user -> modify_password(s1, s2, s3);
        QMessageBox::information(nullptr, "Notice", "修改密码成功");
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

inline void UserOperation::set_single_string(const string &_s1) {
    s1 = _s1;
}

void UserOperation::on_nameButton_clicked()
{
    GetString getstring;
    s1 = "";
    getstring.give_information("新的用户名");
    QDialog::connect(&getstring, &GetString::queried, this, &UserOperation::set_single_string);
    try {
        getstring.exec();
        if (s1 == "") {
            return;
        }
        user -> modify_name(s1);
        QMessageBox::information(nullptr, "Notice", "成功修改用户名为" +
                                 QString::fromStdString(user -> query_name()));
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void UserOperation::on_codeButton_clicked()
{
    QMessageBox::information(nullptr, "Warning", "逗你玩儿呢！去管理员菜单找找吧！");
    return;

    GetString getstring;
    s1 = "";
    getstring.give_information("新的公司验证码");
    QDialog::connect(&getstring, &GetString::queried, this, &UserOperation::set_single_string);
    try {
        getstring.exec();
        if (s1 == "") {
            return;
        }
        user -> set_identifying_code(user -> query_identifying_code(), s1);
        QMessageBox::information(nullptr, "Notice", "成功修改公司验证码为" +
                                 QString::fromStdString(s1));
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void UserOperation::on_logButton_clicked()
{
    /*GetString getstring;
    QDialog::connect(&getstring, &GetString::queried, this, &UserOperation::set_single_string);
    */
    PlainTable ptable;
    ptable.set_user(user);
    ptable.exec();
}

void UserOperation::on_ticketButton_clicked()
{
    TicketTable ttable;
    ttable.set_user(user);
    ttable.exec();
}

void UserOperation::on_infoButton_clicked()
{
    GetString getstring;
    s1 = "";
    getstring.give_information("要查询的用户ID");
    QDialog::connect(&getstring, &GetString::queried, this, &UserOperation::set_single_string);
    try {
        getstring.exec();
        if (s1 == "") {
            return;
        }
        QMessageBox::information(nullptr, "用户基本信息", QString::fromStdString(user -> query_info(s1)));
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void UserOperation::on_chargeButton_2_clicked()
{
    try {
        QMessageBox::information(nullptr, "账户余额", "账户余额为" + QString::fromStdString(sjtu::double_to_string(user -> query_money())));
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}
