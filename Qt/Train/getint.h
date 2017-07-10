#ifndef GETINT_H
#define GETINT_H

#include <QDialog>
#include <iostream>

namespace Ui {
class GetInt;
}

class GetInt : public QDialog
{
    Q_OBJECT

public:
    explicit GetInt(QWidget *parent = 0);
    ~GetInt();
    void set_bound(int _bound);
    void send_int(int number) {
        //std::cout << "get_int emit number" << std::endl;
        emit queried(number);
    }

private slots:
    void on_quitBtn_clicked();

    void on_enterBtn_clicked();

signals:
    void queried(int number);

private:
    Ui::GetInt *ui;
    int bound;
};

#endif // GETINT_H

