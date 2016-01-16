#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void OnStart();
    void OnRequest();
    void closeEvent ( QCloseEvent * e );
    Ui::MainWindow *ui;
private slots:
    void on_commandLinkButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_listWidget_clicked(const QModelIndex &index);
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_13_triggered();
    void on_action_3_triggered();
    void on_action_7_triggered();
    void on_action_6_triggered();
    void on_action_11_triggered();
    void on_action_9_triggered();
    void on_action_5_triggered();
    void on_action_8_triggered();
    void on_action_4_triggered();
    void on_pushButton_clicked();
    void on_action_10_triggered();
    void on_pushButton_4_clicked();
    void on_textBrowser_anchorClicked(const QUrl &arg1);
};

#endif // MAINWINDOW_H
