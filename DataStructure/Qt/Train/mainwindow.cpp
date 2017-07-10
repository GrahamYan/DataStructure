#include "mainwindow.h"
#include "fromfile.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "register.h"
#include "queryticket.h"
#include "queryticket.cpp"
#include "getint.h"
#include "getint.cpp"
#include "useroperation.h"
#include "adminoperation.h"
#include <QDateTimeEdit>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include <iostream>
#include <QString>

using namespace sjtu;

//MainWindow::MainWindow(shared_ptr<QWidget> parent) :
void MainWindow::set_user(shared_ptr<User> _user) {
    user = _user;
}

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui -> setupUi(this);
    setWindowTitle("羊羊火车票");
   // setWindowIcon(QIcon(":images/pictures/班徽.png"));
    /*QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
    ui -> label -> setText(str);
*/
    /*QTimer *timer = new QTimer(this);
    //关联定时器溢出信号和相应的槽函数
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    timer->start(1000);*/
    //QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    //connect(dateTimeEdit, SIGNAL(dateChanged(QDate)), this, SLOT(onDateChanged(QDate)));
}

MainWindow::~MainWindow()
{
    //delete ui;
}

/*inline void MainWindow::timerUpdate() {
    QDateTime time = QDateTime::currentDateTime();
     //设置系统时间显示格式
     QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd");
     //在标签上显示时间
     ui->lineEdit->setText(str);
}*/

/*void onDateChanged(const QDate &date) {
    qDebug() << "QDate : " << date;
}*/

vector<string> get_all_level(string &obj) {
    vector<string> ret;
    ret.clear();
    obj = obj + ',';
    string s = "";
    for (int i = 0; i < (int)obj.size(); ++i) {
        if (obj[i] == ',') {
            ret.push_back(s);
            s = "";
        } else {
            s = s + obj[i];
        }
    }
    return ret;
}

void MainWindow::list_tickets(const string &train_id, const string &start_lo, const string &finish_lo, const string &date1, const string &date2, const string &level, int number) {
    //std::cout << "sdfsdafasdfsadfasfsadfdasfsfasdf" << std::endl;
    shared_ptr<vector<Tickets> > ticket;
    string temp_level = level;
    vector<string> all_level = get_all_level(temp_level);
    if (train_id == "") {
        ticket = user -> query_ticket(date1, date2, start_lo, finish_lo, all_level, number);
    } else {
        ticket = user -> query_ticket_by_id(train_id, start_lo, finish_lo, date1, date2, all_level, number);
    }

    model = new QStandardItemModel();
    model -> setColumnCount(8);
    model -> setHeaderData(0, Qt::Horizontal, tr("车次"));
    model -> setHeaderData(1, Qt::Horizontal, tr("火车日期"));
    model -> setHeaderData(2, Qt::Horizontal, tr("出站日期"));
    model -> setHeaderData(3, Qt::Horizontal, tr("起点"));
    model -> setHeaderData(4, Qt::Horizontal, tr("终点"));
    model -> setHeaderData(5, Qt::Horizontal, tr("票型"));
    model -> setHeaderData(6, Qt::Horizontal, tr("张数"));
    model -> setHeaderData(7, Qt::Horizontal, tr("单价"));
    //model -> setHeaderData(7, Qt::Horizontal, tr("购买"));
    ui -> tableView -> setModel(model);
    ui -> tableView -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> tableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui -> tableView -> setSortingEnabled(true);
  //  ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
   /* model -> setItem(0, 0, new QStandardItem("12321321"));
    model -> setItem(1, 0, new QStandardItem("086"));
    model -> setItem(2, 0, new QStandardItem("546345"));
    for(int i = 0; i < 3; i++)
    {
         //model->setItem(i,0,new QStandardItem(213123));
            //设置字符颜色
         model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
            //设置字符位置
         model->item(i,0)->setTextAlignment(Qt::AlignCenter);
         model->setItem(i,1,new QStandardItem(QString::fromLocal8Bit("哈哈")));
    }*/
    for (int i = 0; i < (int)ticket -> size(); ++i) {
        model -> setItem(i, 0, new QStandardItem(QString::fromStdString((*ticket)[i].query_id())));
        model -> setItem(i, 1, new QStandardItem(QString::fromStdString((*ticket)[i].query_train_date().print())));
        model -> setItem(i, 2, new QStandardItem(QString::fromStdString((*ticket)[i].query_departure_date().print())));
        model -> setItem(i, 3, new QStandardItem(QString::fromStdString((*ticket)[i].query_start_station())));
        model -> setItem(i, 4, new QStandardItem(QString::fromStdString((*ticket)[i].query_finish_station())));
        model -> setItem(i, 5, new QStandardItem(QString::fromStdString((*ticket)[i].query_level())));
        model -> setItem(i, 6, new QStandardItem(QString::number((*ticket)[i].query_number())));
        model -> setItem(i, 7, new QStandardItem(QString::number((*ticket)[i].query_price())));
        //model -> setItem(i, 7, new QStandardItem(*ticket)[i]);
    }
}

void MainWindow::on_login_button_clicked()
{
    Login login;
    login.set_user(this -> user);
    login.exec();
    if (user -> check_login()) {
        ui -> now_user -> setText(QString::fromStdString(user -> query_now_id()));
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    user -> logout();
    QMessageBox::information(nullptr, "Notice", "登出");
    ui -> now_user -> setText(tr("未登录"));
}

void MainWindow::on_regigster_button_clicked()
{
    Register reg;
    reg.set_user(this -> user);
    reg.exec();
}

void MainWindow::test() {
    std::cout << "I'm here!" << std::endl;
}

void MainWindow::on_queryTicket_clicked()
{
    QueryTicket que;
    que.set_user(this -> user);
    QDialog::connect(&que, &QueryTicket::queried, this, &MainWindow::list_tickets);
    que.exec();
   // std::cout << "query finish" << std::endl;
}

inline void MainWindow::buy_tickets_from_list(int number) {
   // std::cout << "buy " << number << std::endl;
    number_with_user = number;
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    /*std::cout << index.data().toString().toStdString() << std::endl;
    std::cout << index.row() << std::endl;*/
    QMessageBox box;
    box.setWindowTitle("Notice");
    box.setIcon(QMessageBox::Warning);
    box.setText(tr("确定要购买该票吗，大哥？"));
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (box.exec() == QMessageBox::No) {
        QMessageBox::information(nullptr, "Notice", "老哥，稳啊！");
    } else {
        GetInt get_int;
        int bound = (model -> item(index.row(), 6) -> text()).toInt();
   //std::cout << index.row() << " " << index.column() << " " << bound << std::endl;
        get_int.set_bound(bound);
        QDialog::connect(&get_int, &GetInt::queried, this, &MainWindow::buy_tickets_from_list);
        get_int.exec();
        if (number_with_user < 0) {
            QMessageBox::information(nullptr, "Warning", "竟敢买负数，你肯定是疯了！！！");
            return;
        }
        if (number_with_user == 0) {
            return;
        }
        string train_id = model -> item(index.row(), 0) -> text().toStdString();
        Date train_date = Date(model -> item(index.row(), 1) -> text().toStdString());
        string start_station = model -> item(index.row(), 3) -> text().toStdString();
        string finish_station = model -> item(index.row(), 4) -> text().toStdString();
        string level = model -> item(index.row(), 5) -> text().toStdString();
        int num = model -> item(index.row(), 6) ->text().toInt();
        try {
            user -> buy_ticket(train_id, train_date, start_station, finish_station, level, number_with_user);
            QMessageBox::information(nullptr, "Notice", "购票成功！");

            model -> setItem(index.row(), 6, new QStandardItem(QString::number(num - number_with_user)));
        }
        catch (const Exception &exc) {
            QMessageBox::information(nullptr, "Notice", QString::fromStdString(exc.detail));
        }
    }
}

void MainWindow::on_userButton_clicked()
{
    UserOperation oper;
    oper.set_user(user);
    oper.exec();
    if (user -> check_login()) {
        ui -> now_user -> setText(QString::fromStdString(user -> query_now_id()));
    }
}

void MainWindow::on_adminButton_clicked()
{
    AdminOperation oper;
    oper.set_user(user);
    oper.exec();
}

#include "QFileDialog"

void MainWindow::on_action_triggered()
{
    QFileDialog w;
    w.setAcceptMode(QFileDialog::AcceptOpen);   //AcceptOpen打开,AcceptSave保存文件
    w.setFileMode(QFileDialog::ExistingFiles);
    w.setOption(QFileDialog::ReadOnly, true);

    w.setWindowTitle(QString("Include train"));
    w.setDirectory(QString("./"));
    w.setNameFilter(QString("所有文件(*.*)"));

    try {
        sjtu::FromFile::get_train_from_file(user, w.getOpenFileName().toStdString(), User::CheckExist::Must);
        QMessageBox::information(nullptr, "Notice", "添加车次成功");
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Notice", QString::fromStdString(exc.detail));
    }
    //sjtu::FromFile::get_train_from_file(user, "../origin_train", User::CheckExist::Opt);
    std::cout << "load train ok" << std::endl;
}
