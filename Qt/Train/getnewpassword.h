#ifndef GETNEWPASSWORD_H
#define GETNEWPASSWORD_H

#include <QDialog>
#include <iostream>

using std::string;

namespace Ui {
class GetNewPassword;
}

class GetNewPassword : public QDialog
{
    Q_OBJECT

public:
    explicit GetNewPassword(QWidget *parent = 0);
    ~GetNewPassword();
    inline void send_string(const string &s1, const string &s2, const string &s3) {
        emit queried(s1, s2, s3);
    }

signals:
    void queried(const string &s1, const string &s2, const string &s3);

private slots:
    void on_quitBtn_clicked();

    void on_getpwd_clicked();

private:
    Ui::GetNewPassword *ui;
    string s1, s2, s3;
};

#endif // GETNEWPASSWORD_H
