#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include "../../src/User.hpp"

using namespace sjtu;

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    void set_user(shared_ptr<User> _user);
    ~Register();

private slots:
    void on_quitBtn_clicked();

    void on_registerBtn_clicked();

private:
    Ui::Register *ui;
    shared_ptr<User> user;
};

#endif // REGISTER_H
