#ifndef GETSTRING_H
#define GETSTRING_H

#include <QDialog>
#include <iostream>
#include <string>

using std::string;

namespace Ui {
class GetString;
}

class GetString : public QDialog
{
    Q_OBJECT

public:
    explicit GetString(QWidget *parent = 0);
    ~GetString();
    void give_information(const string &obj);
    void send_string(const string &obj) {
        emit queried(obj);
    }

signals:
    void queried(const string &obj);

private slots:
    void on_quitBtn_clicked();

    void on_enterBtn_clicked();

private:
    Ui::GetString *ui;
    string str;
};

#endif // GETSTRING_H

