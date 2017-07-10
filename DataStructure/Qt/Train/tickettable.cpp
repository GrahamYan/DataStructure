#include "tickettable.h"
#include "ui_tickettable.h"
#include "getint.h"
#include "../../src/Log.hpp"
#include "../../src/GeneralUser.hpp"
#include "../../src/lib/ptr.hpp"
#include "../../src/lib/vector.hpp"
#include "../../src/Tickets.hpp"
#include <QStandardItemModel>
#include <QMessageBox>

TicketTable::TicketTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketTable)
{
    ui->setupUi(this);
}

TicketTable::~TicketTable()
{
    delete ui;
}

void TicketTable::set_user(shared_ptr<User> _user) {
    user = _user;
}

void TicketTable::output_ticket(const string &user_id) {
    try {
        shared_ptr<vector<Tickets> > ticket = user -> query_my_tickets(user_id);
        model = new QStandardItemModel();
        model -> setColumnCount(8);
        model -> setHeaderData(0, Qt::Horizontal, tr("车次"));
        model -> setHeaderData(1, Qt::Horizontal, tr("发车时间"));
        model -> setHeaderData(2, Qt::Horizontal, tr("起点"));
        model -> setHeaderData(3, Qt::Horizontal, tr("终点"));
        model -> setHeaderData(4, Qt::Horizontal, tr("出站时间"));
        model -> setHeaderData(5, Qt::Horizontal, tr("票型"));
        model -> setHeaderData(6, Qt::Horizontal, tr("单价"));
        model -> setHeaderData(7, Qt::Horizontal, tr("张数"));

        ui -> tableView -> setModel(model);
        ui -> tableView -> setSelectionBehavior(QAbstractItemView::SelectRows);
        ui -> tableView -> setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui -> tableView -> setSortingEnabled(true);
        ui->tableView->setStyleSheet("QTableView {\
                                                            font:12px;\
            border:1px solid #a0a0a0;\
            border-top:0;\
                                                        }");

        int size = ticket -> size();
        for (int i = 0; i < size; ++i) {
            model -> setItem(i, 0, new QStandardItem(QString::fromStdString((*ticket)[i].query_id())));
            model -> setItem(i, 1, new QStandardItem(QString::fromStdString((*ticket)[i].query_train_date().print())));
            model -> setItem(i, 2, new QStandardItem(QString::fromStdString((*ticket)[i].query_start_station())));
            model -> setItem(i, 3, new QStandardItem(QString::fromStdString((*ticket)[i].query_finish_station())));
            model -> setItem(i, 4, new QStandardItem(QString::fromStdString((*ticket)[i].query_departure_date().print())));
            model -> setItem(i, 5, new QStandardItem(QString::fromStdString((*ticket)[i].query_level())));
            model -> setItem(i, 6, new QStandardItem(QString::fromStdString(sjtu::double_to_string(((*ticket)[i].query_price())))));
            model -> setItem(i, 7, new QStandardItem(QString::number((*ticket)[i].query_number())));
            //model -> setItem(i, 0, new QStandardItem(QString::fromStdString((*log)[i])));
            //model -> item(i,0) -> setTextAlignment(Qt::AlignCenter);
        }
        ui -> tableView -> resizeColumnsToContents();
    }
    catch (const Exception &exc) {
        QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
        return;
    }
}

void TicketTable::on_quitButton_clicked()
{
    close();
}

void TicketTable::on_enterButton_clicked()
{
    string str = ui -> userEdit ->text().toStdString();
    output_ticket(str);
}

void TicketTable::refund_tickets_from_list(int number) {
    number_with_user = number;
}

void TicketTable::on_tableView_doubleClicked(const QModelIndex &index)
{
    QMessageBox box;
    box.setWindowTitle("Notice");
    box.setIcon(QMessageBox::Warning);
    box.setText(tr("确定要退该种该票吗，大哥？"));
    box.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    if (box.exec() == QMessageBox::No) {
        QMessageBox::information(nullptr, "Notice", "老哥，还是这么稳啊！");
    } else {
        GetInt get_int;
        int bound = (model -> item(index.row(), 7) -> text()).toInt();
        get_int.set_bound(bound);
        QDialog::connect(&get_int, &GetInt::queried, this, &TicketTable::refund_tickets_from_list);
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
        string start_station = model -> item(index.row(), 2) -> text().toStdString();
        string finish_station = model -> item(index.row(), 3) -> text().toStdString();
        string level = model -> item(index.row(), 5) -> text().toStdString();
        try {
            user -> refund_ticket(train_id, train_date, start_station, finish_station, level, number_with_user);
            int i = index.row();
            model -> setItem(i, 7, new QStandardItem(QString::number(bound - number_with_user)));
            QMessageBox::information(nullptr, "Notice", "退票成功！");
        }
        catch (const Exception &exc) {
            QMessageBox::information(nullptr, "Warning", QString::fromStdString(exc.detail));
        }
    }
}
