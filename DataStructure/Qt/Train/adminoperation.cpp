#include "adminoperation.h"
#include "ui_adminoperation.h"

#include <QString>
#include <iostream>
#include <QMessageBox>
#include "../../src/Exceptions.hpp"
#include "getint.h"
#include "getnewpassword.h"
#include "getstring.h"
#include "plaintable.h"
#include "tickettable.h"
#include "gettraininfo.h"
#include "fromfile.h"
#include <string>
#include <QFileDialog>

using std::string;

AdminOperation::AdminOperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminOperation)
{
    ui->setupUi(this);
}

AdminOperation::~AdminOperation()
{
    delete ui;
}

void AdminOperation::set_user(shared_ptr<User> _user) {
    user = _user;
}


/*inline void UserOperation::set_number_with_user(int number)  {
//std::cout << "充值 " << number << std::endl;
    number_with_user = number;
}


void UserOperation::on_chargeButton_clicked()
{
    GetInt getint;
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

inline void UserOperation::set_string(const string &_s1, const string &_s2, const string &_s3) {
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
        QMessageBox::information(nullptr, "Notice", "成功修改用户名为" +
                                 QString::fromStdString(user -> query_name()));
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void UserOperation::on_logButton_clicked()
{
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
*/

void AdminOperation::get_train_info(const string &_train_id, const string &_date1, const string &_date2) {
    train_id = _train_id;
    start_date = Date(_date1);
    finish_date = Date(_date2);
}

void AdminOperation::on_infoButton_clicked()
{
    GetTrainInfo get_train;
    train_id = "";
    QDialog::connect(&get_train, &GetTrainInfo::queried, this, &AdminOperation::get_train_info);
    try {
        get_train.exec();
        if (train_id == "") {
            return;
        }
        user -> start_daily_sale(train_id, start_date, finish_date);
        QMessageBox::information(nullptr, "Notice", "发售车票成功");
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void AdminOperation::on_finishSaleButton_clicked()
{
    GetTrainInfo get_train;
    train_id = "";
    QDialog::connect(&get_train, &GetTrainInfo::queried, this, &AdminOperation::get_train_info);
    try {
        get_train.exec();
        if (train_id == "") {
            return;
        }
        user -> finish_daily_sale(train_id, start_date, finish_date);
        QMessageBox::information(nullptr, "Notice", "停止发售车票成功");
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void AdminOperation::set_single_string(const std::__cxx11::string &_s1) {
    s1 = _s1;
}

void AdminOperation::on_codeButton_clicked()
{
    GetString getstring;
    s1 = "";
    getstring.give_information("新的公司验证码");
    QDialog::connect(&getstring, &GetString::queried, this, &AdminOperation::set_single_string);
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

void AdminOperation::on_finishTrainButton_clicked()
{
    GetTrainInfo get_train;
    train_id = "";
    QDialog::connect(&get_train, &GetTrainInfo::queried, this, &AdminOperation::get_train_info);
    try {
        get_train.exec();
        if (train_id == "") {
            return;
        }
       // user -> finish_daily_sale(train_id, start_date, finish_date);
        user -> delete_daily_route(train_id, start_date, finish_date);
        QMessageBox::information(nullptr, "Notice", "删除车次成功");
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}

void AdminOperation::on_startTrainButton_clicked()
{
    QFileDialog w;
    w.setAcceptMode(QFileDialog::AcceptOpen);   //AcceptOpen打开,AcceptSave保存文件
    w.setFileMode(QFileDialog::ExistingFiles);
    w.setOption(QFileDialog::ReadOnly, true);

    w.setWindowTitle(QString("Include train"));
    w.setDirectory(QString("./"));
    w.setNameFilter(QString("所有文件(*.*)"));
    //ifstream file(w.getOpenFileName().toStdString());
    try {
        sjtu::FromFile::get_train_from_file(user, w.getOpenFileName().toStdString(), User::CheckExist::Must);
        QMessageBox::information(nullptr, "Notice", "添加车次成功");
    }
    catch (const Exception &exc){
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
    }
}
