#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"
#include <QPainter>

QwMainWindow::QwMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QwMainWindow) {
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    setCentralWidget(ui->tabWidget);
    setWindowState(Qt::WindowMaximized);
}

QwMainWindow::~QwMainWindow() {
    delete ui;
}

void QwMainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,
                       ui->toolBar->height(),
                       this->width(),
                       this->height() - ui->toolBar->height() - ui->statusbar->height(),
                       QPixmap(":/imag/back.jpg"));
}
