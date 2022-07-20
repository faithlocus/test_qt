#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QIODevice>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_action_file_open_triggered() {
    QString curPath = QDir::currentPath();
    QString dlgTitle("打开一个文件");
    QString filter("程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (aFileName.isEmpty())
        return;
    openTextByIODevice(aFileName);
}

bool MainWindow::openTextByIODevice(const QString &aFileName) {
    QFile aFile(aFileName);
    if (!aFile.exists())
        return false;
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    ui->plainTextEdit->setPlainText(aFile.readAll());
    aFile.close();
    ui->tabWidget->setCurrentIndex(0);
    return true;
}
