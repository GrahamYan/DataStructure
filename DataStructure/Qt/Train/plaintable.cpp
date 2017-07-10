#include "../../src/Log.hpp"
#include "../../src/GeneralUser.hpp"
#include "../../src/lib/ptr.hpp"
#include "plaintable.h"
#include "ui_plaintable.h"
#include <QStandardItemModel>
#include <QButtonGroup>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QMessageBox>

PlainTable::PlainTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlainTable)
{
    ui->setupUi(this);

    m_pButtonGroup = new QButtonGroup(this);
    m_pButtonGroup->setExclusive(true);
    ui ->radioButton ->setText("全部日志");
    ui ->radioButton_2->setText("买票日志");
    ui ->radioButton_3->setText("退票日志");
    ui ->radioButton_4 ->setText("票务日志");
    ui ->radioButton_5->setText("余额日志");
    m_pButtonGroup -> addButton(ui->radioButton);
    m_pButtonGroup -> addButton(ui->radioButton_2);
    m_pButtonGroup -> addButton(ui->radioButton_3);
    m_pButtonGroup -> addButton(ui->radioButton_4);
    m_pButtonGroup -> addButton(ui->radioButton_5);
}

PlainTable::~PlainTable()
{
    delete ui;
}

void PlainTable::set_user(shared_ptr<User> _user) {
    user = _user;
}

void PlainTable::get_type() {

}

void PlainTable::output_log(const string &user_id, const GeneralUser::LogType &type) {
    QStandardItemModel *model = new QStandardItemModel();
    model -> setColumnCount(1);
    model -> setHeaderData(0, Qt::Horizontal, tr("Log"));
    ui -> tableView -> setModel(model);
    ui -> tableView -> setSelectionBehavior(QAbstractItemView::SelectRows);
    ui -> tableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui -> tableView -> setSortingEnabled(true);
    ui->tableView->setStyleSheet("QTableView {\
                                                        font:12px;\
        border:1px solid #a0a0a0;\
        border-top:0;\
                                                    }");
    try {
        shared_ptr<Log> log = (user_id == "系统日志") ? user -> get_local_log() : user -> query_log(user_id, type);
        int size = log->size();
        for (int i = 0; i < size; ++i) {
            model -> setItem(i, 0, new QStandardItem(QString::fromStdString((*log)[i])));
            //model -> item(i,0) -> setTextAlignment(Qt::AlignCenter);
        }
        ui -> tableView -> resizeColumnToContents(0);
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
        return;
    }
    /*for (int i = 0; i < ticket -> size(); ++i) {
        model -> setItem(i, 0, new QStandardItem(QString::fromStdString((*ticket)[i].query_id())));
        model -> setItem(i, 1, new QStandardItem(QString::fromStdString((*ticket)[i].query_train_date().print())));
        model -> setItem(i, 2, new QStandardItem(QString::fromStdString((*ticket)[i].query_departure_date().print())));
        model -> setItem(i, 3, new QStandardItem(QString::fromStdString((*ticket)[i].query_start_station())));
        model -> setItem(i, 4, new QStandardItem(QString::fromStdString((*ticket)[i].query_finish_station())));
        model -> setItem(i, 5, new QStandardItem(QString::fromStdString((*ticket)[i].query_level())));
        model -> setItem(i, 6, new QStandardItem(QString::number((*ticket)[i].query_number())));
        model -> setItem(i, 7, new QStandardItem(QString::number((*ticket)[i].query_price())));
        //model -> setItem(i, 7, new QStandardItem(*ticket)[i]);
    }*/
}

void PlainTable::on_quitButton_clicked()
{
    close();
}

void PlainTable::on_enterButton_clicked()
{
    string str = ui -> userEdit ->text().toStdString();
    if (str == "系统日志") {
        output_log(str, GeneralUser::LogType::All);
        return;
    }
    if (ui -> radioButton -> isChecked()) {
        output_log(str, GeneralUser::LogType::All);
        return;
    }
    if (ui -> radioButton_2 -> isChecked()) {
        output_log(str, GeneralUser::LogType::Buy);
        return;
    }
    if (ui -> radioButton_3 -> isChecked()) {
        output_log(str, GeneralUser::LogType::Refund);
        return;
    }
    if (ui -> radioButton_4 -> isChecked()) {
        output_log(str, GeneralUser::LogType::BuyAndRefund);
        return;
    }
    if (ui -> radioButton_5 -> isChecked()) {
        output_log(str, GeneralUser::LogType::Charge);
        return;
    }
    QMessageBox::information(nullptr, "Warning", "老哥，你什么都不选，我也很绝望啊");
}
