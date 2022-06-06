#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->slider_r, &QSlider::valueChanged, this, &MainWindow::color_slider_value_changed);
    connect(ui->slider_g, &QSlider::valueChanged, this, &MainWindow::color_slider_value_changed);
    connect(ui->slider_b, &QSlider::valueChanged, this, &MainWindow::color_slider_value_changed);
    connect(ui->slider_a, &QSlider::valueChanged, this, &MainWindow::color_slider_value_changed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::color_slider_value_changed(int value)
{
    Q_UNUSED(value);
    int r = ui->slider_r->value();
    int g = ui->slider_g->value();
    int b = ui->slider_b->value();
    int a = ui->slider_a->value();
    QColor color{};
    color.setRgb(r, g, b, a);
    QPalette pal = ui->te_color->palette();
    pal.setColor(QPalette::Base, color);
    ui->te_color->setPalette(pal);
}


void MainWindow::on_radioButton_clicked(bool checked)
{
    if (!checked)
        return;
    ui->lcdNumber->setBinMode();
    ui->lcdNumber->setDigitCount(8);
    update_lcd_value();
}


void MainWindow::on_radioButton_2_clicked(bool checked)
{
    if (!checked)
        return;
    ui->lcdNumber->setOctMode();
    ui->lcdNumber->setDigitCount(3);
    update_lcd_value();
}


void MainWindow::on_radioButton_3_clicked(bool checked)
{
    if (!checked)
        return;
    ui->lcdNumber->setDecMode();
    ui->lcdNumber->setDigitCount(2);
    update_lcd_value();
}


void MainWindow::on_radioButton_4_clicked(bool checked)
{
    if (!checked)
        return;
    ui->lcdNumber->setHexMode();
    ui->lcdNumber->setDigitCount(2);
    update_lcd_value();
}

void MainWindow::update_lcd_value()
{
    int value = ui->dial->value();
    ui->lcdNumber->display(value);
}


void MainWindow::on_horizontalScrollBar_valueChanged(int value)
{
    ui->progressBar->setValue(value);
}



void MainWindow::on_progressBar_valueChanged(int value)
{
    ui->horizontalScrollBar->setValue(value);

}

