#ifndef AUIMANAGER_H
#define AUIMANAGER_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include "registr.h"
#include "ui_registr.h"
#include "form.h"
#include "ui_form.h"
#include "kabinet.h"
#include "ui_kabinet.h"
#include "loading.h"
#include "ui_loading.h"
class UIModule
{
public:
    MainWindow *Main;
    Ui::MainWindow *MainUI;
    Kabinet *Kabin;
    Ui::Kabinet *KabinUI;
    Form *Message;
    Ui::Form *MessageUI;
    registr *Reg;
    Ui::registr *RegUI;
    Dialog *LoadMenu;
    Ui::Dialog *LoadMenuUI;
    Loading *LoadWindow;
    Ui::Loading *LoadWindowUI;
};
extern UIModule *R;


#endif // AUIMANAGER

