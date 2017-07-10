#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "../../src/User.hpp"

using namespace sjtu;

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void set_user(shared_ptr<User> _user);
    ~Login();

private slots:
    void on_loginBtn_clicked();

    void on_logoutBtn_clicked();

private:
    Ui::Login *ui;
    shared_ptr<User> user;
};

#endif // LOGIN_H
