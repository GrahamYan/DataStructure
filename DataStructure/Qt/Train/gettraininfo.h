#ifndef GETTRAININFO_H
#define GETTRAININFO_H

#include <QDialog>
#include <string>

using std::string;

namespace Ui {
class GetTrainInfo;
}

class GetTrainInfo : public QDialog
{
    Q_OBJECT

public:
    explicit GetTrainInfo(QWidget *parent = 0);
    ~GetTrainInfo();
    void send_info(const string &train_id, const string &date1, const string &date2) {
        //std::cout << "get_int emit number" << std::endl;
        emit queried(train_id, date1, date2);
    }

private slots:
    void on_quitButton_clicked();

    void on_enterButton_clicked();

signals:
    void queried(const string &train_id, const string &date1, const string &date2);

private:
    Ui::GetTrainInfo *ui;
};

#endif // GETTRAININFO_H
