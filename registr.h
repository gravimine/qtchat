#ifndef REGISTR_H
#define REGISTR_H

#include <QDialog>

namespace Ui {
class registr;
}

class registr : public QDialog
{
    Q_OBJECT

public:
    explicit registr(QWidget *parent = 0);
    ~registr();
Ui::registr *ui;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

};

#endif // REGISTR_H
