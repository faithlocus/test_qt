#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, &MainWindow::timer_timeout);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushbtn_now_clicked()
{
    auto now = QDateTime::currentDateTime();
    auto date = now.date();
    auto time = now.time();
    ui->label_now->setText(now.toString());
    ui->timeEdit->setTime(time);
    ui->lineEdit_time->setText(time.toString());
    ui->dateEdit->setDate(date);
    ui->lineEdit_date->setText(date.toString());
    ui->dateTimeEdit->setDateTime(now);
    ui->lineEdit_datetime->setText(now.toString());
}


void MainWindow::on_calendarWidget_currentPageChanged(int year, int month)
{
    int a;
}


void MainWindow::on_calendarWidget_selectionChanged()
{
    auto date = ui->calendarWidget->selectedDate();
    ui->dateEdit->setDate(date);
    ui->lineEdit_date->setText(date.toString());
}


void MainWindow::on_pushButton_timer_set_clicked()
{
    int interval = ui->lineEdit_timer_dur->text().toInt();
    timer.setInterval(interval);
}


void MainWindow::on_pushButton_start_timer_clicked()
{
    timer.start();
}


void MainWindow::on_pushButton_stop_timer_clicked()
{
    timer.stop();
    ui->lable_dur->setText("");
}

void MainWindow::timer_timeout()
{
    auto pre = ui->lable_dur->text().toInt();
    int interval = ui->lineEdit_timer_dur->text().toInt();
    ui->lable_dur->setText(QString::number(pre + interval));
}


