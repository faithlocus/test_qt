#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"
#include <QWidget>

QwMainWindow::QwMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QwMainWindow) {
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
}

QwMainWindow::~QwMainWindow() {
    delete ui;
}
