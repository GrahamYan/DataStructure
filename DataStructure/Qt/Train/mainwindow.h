#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStandardItemModel>
#include "../../src/lib/ptr.hpp"
#include "../../src/GeneralUser.hpp"
#include "../../src/User.hpp"

using namespace sjtu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void set_user(shared_ptr<User> _user);
    //explicit MainWindow(shared_ptr<QWidget> parent = nullptr);
    ~MainWindow();
    void list_tickets(const string &train_id, const string &start_lo, const string &finish_lo, const string &date1, const string &date2, const string &level, int number);
    void buy_tickets_from_list(int number);
    void test();

private slots:
    void on_login_button_clicked();

    void on_pushButton_2_clicked();

    void on_regigster_button_clicked();

    void on_queryTicket_clicked();
    
    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_userButton_clicked();

    void on_adminButton_clicked();

    void on_action_triggered();

private:
    shared_ptr<User> user;
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    int number_with_user;
    //shared_ptr<Ui::MainWindow> ui;
};

#endif // MAINWINDOW_H
