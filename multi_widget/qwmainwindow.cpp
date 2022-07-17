#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"
#include <QPainter>

#include "qformdoc.h"

QwMainWindow::QwMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::QwMainWindow) {
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();
    ui->tabWidget->setTabsClosable(true);
    setCentralWidget(ui->tabWidget);
    setWindowState(Qt::WindowMaximized);
    initSignalSlot();
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

void QwMainWindow::initSignalSlot() {
    connect(ui->actionembedded_widget_action,
            &QAction::triggered,
            this,
            &QwMainWindow::on_action_insidewidget_triggered);
    connect(ui->actionindependent_widget_action,
            &QAction::triggered,
            this,
            &QwMainWindow::on_action_widget_triggered);
}

void QwMainWindow::on_action_insidewidget_triggered() {
    QFormDoc *formdoc = new QFormDoc();
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formdoc, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QwMainWindow::on_action_widget_triggered() {
    QFormDoc *formdoc = new QFormDoc(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    formdoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");
    formdoc->setWindowFlag(Qt::Window, true);
    formdoc->setWindowOpacity(0.9);
    formdoc->show();
}
