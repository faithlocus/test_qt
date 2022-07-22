#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>

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

void MainWindow::on_action_file_saveas_triggered() {
    QString curPath = QDir::currentPath();
    QString dlgTitle{ "另存为一个文件" };
    QString filter{ "h文件(*.h);;cpp文件(*.cpp);;所有文件(*.*)" };
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (aFileName.isEmpty())
        return;
    saveTextByIODevice(aFileName);
}

bool MainWindow::saveTextByIODevice(const QString &aFileName) {
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QString    str      = ui->plainTextEdit->toPlainText();
    QByteArray strBytes = str.toUtf8();
    aFile.write(strBytes, strBytes.length());
    aFile.close();
    ui->tabWidget->setCurrentWidget(0);
    return true;
}

void MainWindow::on_action_stream_open_triggered() {
    QString curPath = QDir::currentPath();
    QString dlgTitle{ "打开一个文件" };
    QString filter("程序文件(*.h *.cpp);;文本文件(*.txt);;所有文件(*.*)");
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (aFileName.isEmpty())
        return;
    openTextByStream(aFileName);
}

bool MainWindow::openTextByStream(const QString &aFileName) {
    QFile aFile(aFileName);
    if (!aFile.exists())
        return false;

    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    ui->plainTextEdit_2->clear();
    QString str{};
    while (!aStream.atEnd()) {
        str = aStream.readLine();
        ui->plainTextEdit_2->appendPlainText(str);
    }
    aFile.close();
    return true;
}

void MainWindow::on_action_stream_saveas_triggered() {
    QString curPath = QDir::currentPath();
    QString dlgTitle{ "另存为一个文件" };
    QString filter{ "h文件(*.h);;cpp文件(*.cpp);;所有文件(*.*)" };
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (aFileName.isEmpty())
        return;
    saveTextByStream(aFileName);
}

bool MainWindow::saveTextByStream(const QString &aFileName) {
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QTextStream aStream(&aFile);
    aStream.setAutoDetectUnicode(true);
    QString str = ui->plainTextEdit_2->toPlainText();
    aStream << str;
    aFile.close();
    return true;
}
