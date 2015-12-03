#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
Ui::Form *ui;
private slots:
    void on_pushButton_clicked();


};

#endif // FORM_H
