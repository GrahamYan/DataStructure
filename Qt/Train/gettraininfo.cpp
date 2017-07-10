#include "gettraininfo.h"
#include "ui_gettraininfo.h"
#include <QString>

GetTrainInfo::GetTrainInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetTrainInfo)
{
    ui->setupUi(this);
}

GetTrainInfo::~GetTrainInfo()
{
    delete ui;
}

void GetTrainInfo::on_quitButton_clicked()
{
    close();
}

void GetTrainInfo::on_enterButton_clicked()
{
    string train_id =ui -> trainEdit -> text().toStdString();
    string date1 = (ui -> dateTimeEdit-> dateTime()).toString("yyyy-MM-dd,hh:mm").toStdString();
    string date2 = (ui -> dateTimeEdit_2-> dateTime()).toString("yyyy-MM-dd,hh:mm").toStdString();
    send_info(train_id, date1, date2);
    close();
}
