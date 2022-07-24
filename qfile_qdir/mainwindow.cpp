#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

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
    ui->plainTextEdit->appendPlainText(theButton->toolTip() + "\n");
}


void MainWindow::on_pushButton_clicked()
{
    showBtnInfo(sender());
    QString dirPath = QCoreApplication::applicationDirPath();
    ui->plainTextEdit->appendPlainText(dirPath);
}


void MainWindow::on_pushButton_2_clicked()
{
    showBtnInfo(sender());
    QString file_path = QCoreApplication::applicationFilePath();
    ui->plainTextEdit->appendPlainText(file_path);
}


void MainWindow::on_pushButton_3_clicked()
{
    showBtnInfo(sender());
    QString file_path = QCoreApplication::applicationName();
    ui->plainTextEdit->appendPlainText(file_path);
}


void MainWindow::on_pushButton_4_clicked()
{
    showBtnInfo(sender());
    auto paths = QCoreApplication::libraryPaths();
    foreach (auto path, paths)
        ui->plainTextEdit->appendPlainText(path);
}


void MainWindow::on_pushButton_5_clicked()
{
    showBtnInfo(sender());
    QString dlgTitle = "setOrgnizationName";
    QString txtLable = "please";
    QString defaultInput = "sorry";
    QLineEdit::EchoMode echoMode = QLineEdit::Normal;
    bool ok = false;
    QString text = QInputDialog::getText(this, dlgTitle, txtLable, echoMode, defaultInput, &ok);
    if (ok)
        QCoreApplication::setOrganizationName(text);
}


void MainWindow::on_pushButton_6_clicked()
{
    showBtnInfo(sender());
    QString name = QCoreApplication::organizationName();
    ui->plainTextEdit->appendPlainText(name);
}


void MainWindow::on_pushButton_7_clicked()
{
    showBtnInfo(sender());
    QCoreApplication::exit();
}

