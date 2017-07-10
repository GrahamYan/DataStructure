#ifndef QUERYTICKET_H
#define QUERYTICKET_H

#include <QDialog>
#include <QObject>
#include "../../src/User.hpp"
#include "../../src/lib/ptr.hpp"

using namespace sjtu;

namespace Ui {
class QueryTicket;
}

class QueryTicket : public QDialog
{
    Q_OBJECT

public:
    explicit QueryTicket(QWidget *parent = 0);
    void set_user(shared_ptr<User> _user);
    ~QueryTicket();
    void send_information(const string &train_id, const string &start_lo, const string &finish_lo, const string &date1, const string &date2, const string &level, int number) {
        emit queried(train_id, start_lo, finish_lo, date1, date2, level, number);
        //std::cout << "adsfsadfsdaf" << std::endl;
    }
    /*void send_information(const string &date) {
        emit queried(date);
        std::cout << "emit ok" << std::endl;
    }*/

private slots:
    void on_quitBtn_clicked();

    void on_queryBtn_clicked();

private:
    Ui::QueryTicket *ui;
    shared_ptr<User> user;

signals:
    void queried(const string &train_id, const string &start_lo, const string &finish_lo, const string &date1, const string &date2, const string &level, int number);
    //void queried(const string &date);
};

#endif
