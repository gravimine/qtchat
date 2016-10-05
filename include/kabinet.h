#ifndef KABINET_H
#define KABINET_H

#include <QDialog>
#include <QButtonGroup>
#include <QListWidgetItem>
namespace Ui {
class Kabinet;
}

class Kabinet : public QDialog
{
    Q_OBJECT

public:
    explicit Kabinet(QWidget *parent = 0);
    ~Kabinet();
Ui::Kabinet *ui;
private slots:

    void on_checkBox_clicked(bool checked);
    void on_checkBox_2_clicked(bool checked);
    void on_pushButton_clicked();
    void on_checkBox_5_stateChanged(int arg1);
    void on_checkBox_7_stateChanged(int arg1);
    void on_tabWidget_currentChanged(int index);
    void on_listWidget_clicked(const QModelIndex &index);
    void on_listWidget_3_clicked(const QModelIndex &index);
    void on_listWidget_2_clicked(const QModelIndex &index);
    void on_pushButton_CreateRoom_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_listWidget_4_clicked(const QModelIndex &index);
    void on_pushButton_9_clicked();
    void on_pushButton_6_clicked();

};

#endif // KABINET_H
