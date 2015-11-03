#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_3_clicked();


private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
