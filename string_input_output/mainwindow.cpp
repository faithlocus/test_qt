#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), num_(0) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pb_calc_clicked()
{
    // int count = ui->le_count->text().toInt();
    // double price = ui->le_price->text().toDouble();
    // double total = count * price;
    // ui->le_total->setText(QString::number(total));

    int num = ui->spinBox->value();
    float price = ui->doubleSpinBox->value();
    ui->doubleSpinBox_2->setValue(num * price);
}

void MainWindow::updateNum()
{
    ui->le_2->setText(QString::number(num_, 2));
    ui->le_8->setText(QString::number(num_, 8));
    ui->le_10->setText(QString::number(num_, 10));
    ui->le_16->setText(QString::number(num_, 16));
}

void MainWindow::on_le_2_textChanged(const QString &arg1)
{
    bool ok{false};
    num_ = arg1.toInt(&ok, 2);
    updateNum();
}

void MainWindow::on_le_8_textChanged(const QString &arg1)
{
    bool ok{false};
    num_ = arg1.toInt(&ok, 8);
    updateNum();
}

void MainWindow::on_le_10_textChanged(const QString &arg1)
{
    // 文本变更时响应
    bool ok{false};
    num_ = arg1.toInt(&ok, 10);
    updateNum();
}

void MainWindow::on_le_16_textChanged(const QString &arg1)
{
    bool ok{false};
    num_ = arg1.toInt(&ok, 16);
    updateNum();
}

void MainWindow::on_le_2_editingFinished() {}


void MainWindow::on_le_10_editingFinished()
{
    //editingFinished光标离开时响应
    bool ok{false};
    num_ = ui->le_10->text().toInt(&ok, 10);
    updateNum();
}

