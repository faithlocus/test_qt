#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"
#include <QPainter>

#include "qformdoc.h"
#include "qformtable.h"

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
    connect(ui->actionembedded_mainwindow_action,
            &QAction::triggered,
            this,
            &QwMainWindow::on_action_insidemainwindow_triggered);
    connect(ui->actionindependent_mainwindow_action,
            &QAction::triggered,
            this,
            &QwMainWindow::on_action_mainwindow_triggered);
}

void QwMainWindow::on_action_insidewidget_triggered() {
    QFormDoc *formdoc = new QFormDoc(this);
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    int cur = ui->tabWidget->addTab(formdoc, QString::asprintf("Doc %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QwMainWindow::on_action_widget_triggered() {
    QFormDoc *formdoc = new QFormDoc();
    formdoc->setAttribute(Qt::WA_DeleteOnClose);
    formdoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");
    formdoc->setWindowFlag(Qt::Window, true);
    formdoc->setWindowOpacity(0.9);
    formdoc->show();
}

void QwMainWindow::on_action_insidemainwindow_triggered() {
    QFormTable *formtable = new QFormTable();
    formtable->setAttribute(Qt::WA_DeleteOnClose);
    int cur =
        ui->tabWidget->addTab(formtable, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}

void QwMainWindow::on_action_mainwindow_triggered() {
    QFormTable *formtable = new QFormTable(this);
    formtable->setAttribute(Qt::WA_DeleteOnClose);
    formtable->setWindowTitle("基于QMainWindow的窗口，指定福窗体，关闭时删除");
    formtable->show();
}

void QwMainWindow::on_tabWidget_currentChanged(int index) {
    Q_UNUSED(index);
    bool en = ui->tabWidget->count() > 0;
    ui->tabWidget->setVisible(en);
}

void QwMainWindow::on_tabWidget_tabCloseRequested(int index) {
    if (index < 0)
        return;
    QWidget *aForm = ui->tabWidget->widget(index);
    aForm->close();
}
