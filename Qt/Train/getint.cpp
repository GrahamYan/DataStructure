#include "getint.h"
#include "ui_getint.h"
#include <QDebug>

GetInt::GetInt(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetInt)
{
    ui->setupUi(this);
}

GetInt::~GetInt()
{
    delete ui;
}

void GetInt::set_bound(int _bound) {
    bound = _bound;
//std::cout << bound << std::endl;
    ui ->request ->setText(tr("请输入数量，上限为") + QString::number(bound));
}

void GetInt::on_quitBtn_clicked()
{
//std::cout << "quit getint" << std::endl;
    close();
}

void GetInt::on_enterBtn_clicked()
{
//std::cout << "enter getint" << std::endl;
    send_int(ui -> numEdit -> text().toInt());
    close();
}
