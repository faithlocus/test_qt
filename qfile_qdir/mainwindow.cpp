#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showBtnInfo(QObject *btn)
{
    QPushButton *theButton = static_cast<QPushButton *>(btn);
    ui->plainTextEdit->appendPlainText(theButton->text());
    ui->plainTextEdit->appendPlainText(theButton->toolTip());
}


void MainWindow::on_pushButton_clicked()
{
    showBtnInfo(sender());
}

