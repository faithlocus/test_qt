#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"

QwMainWindow::QwMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QwMainWindow) {
    ui->setupUi(this);
}

QwMainWindow::~QwMainWindow() {
    delete ui;
}
