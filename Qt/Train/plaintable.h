#ifndef PLAINTABLE_H
#define PLAINTABLE_H

#include <QDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QStandardItemModel>
#include "../../src/lib/ptr.hpp"
#include "../../src/User.hpp"
#include "../../src/GeneralUser.hpp"

using namespace sjtu;

namespace Ui {
class PlainTable;
}

class PlainTable : public QDialog
{
    Q_OBJECT

public:
    explicit PlainTable(QWidget *parent = 0);
    ~PlainTable();
    void set_user(shared_ptr<User> _user);
    void output_log(const string &user_id, const GeneralUser::LogType &type);
    void get_type();

private slots:

    void on_quitButton_clicked();

    void on_enterButton_clicked();

private:
    Ui::PlainTable *ui;
    shared_ptr<User> user;
    QButtonGroup  *m_pButtonGroup;
};

#endif // PLAINTABLE_H
