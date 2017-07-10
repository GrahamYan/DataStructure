#ifndef ADMINOPERATION_H
#define ADMINOPERATION_H

#include <QDialog>
#include <string>
#include "../../src/User.hpp"
#include "../../src/lib/ptr.hpp"
#include "../../src/Date.hpp"

using std::string;
using namespace sjtu;

namespace Ui {
class AdminOperation;
}

class AdminOperation : public QDialog
{
    Q_OBJECT

public:
    explicit AdminOperation(QWidget *parent = 0);
    ~AdminOperation();
    void set_user(sjtu::shared_ptr<User> _user);
    void get_train_info(const string &_train_id, const string &_date1, const string &_date2);
    void set_string(const string &_s1, const string &_s2, const string &_s3);
    void set_single_string(const string &_s1);

private slots:
    void on_infoButton_clicked();

    void on_finishSaleButton_clicked();

    void on_codeButton_clicked();

    void on_finishTrainButton_clicked();

    void on_startTrainButton_clicked();

private:
    Ui::AdminOperation *ui;
    sjtu::shared_ptr<User> user;
    string train_id;
    Date start_date, finish_date;
    string s1, s2, s3;
};

#endif // ADMINOPERATION_H


/*class UserOperation : public QDialog
{
    Q_OBJECT

public:
    explicit UserOperation(QWidget *parent = 0);
    ~UserOperation();
    void set_user(sjtu::shared_ptr<User> _user);
    inline void set_number_with_user(int number);
    inline void set_string(const string &_s1, const string &_s2, const string &_s3);
    inline void set_single_string(const string &_s1);

private:
    Ui::UserOperation *ui;
    sjtu::shared_ptr<User> user;
    int number_with_user;
    string s1, s2, s3;
};

#endif // USEROPERATION_H
*/
