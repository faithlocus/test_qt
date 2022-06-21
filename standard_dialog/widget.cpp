#include "widget.h"
#include "ui_widget.h"
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clear_clicked()
{
    ui->plainTextEdit->clear();
}


void Widget::on_pushButton_open_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "select one file";
    QString filter = "text file(*.txt);;pic file(*.jpg *.gif);;all files(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}


void Widget::on_pushButton_opens_clicked()
{
    QString curPath = QDir::currentPath();
    QString dlgTitle = "select one file";
    QString filter = "text file(*.txt);;pic file(*.jpg *.gif);;all files(*.*)";
    QStringList aFileNames = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
    for (QString filename : aFileNames)
        ui->plainTextEdit->appendPlainText(filename);
}


void Widget::on_pushButton_sel_folder_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "select one dir";
    QString selectDir = QFileDialog::getExistingDirectory(this,
                                                          dlgTitle,
                                                          curPath,
                                                          QFileDialog::ShowDirsOnly);
    if (!selectDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectDir);
}


void Widget::on_pushButton_save_clicked()
{
    QString curPath = QCoreApplication::applicationDirPath();
    QString dlgTitle = "save file";
    QString filter = "h file(*.h);;cpp file(*.cpp);;all file(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}


void Widget::on_pushButton_sel_color_clicked()
{
    QPalette pal = ui->plainTextEdit->palette();
    QColor iniColor = pal.color(QPalette::Text);
    auto color = QColorDialog::getColor(iniColor, this, "save color");
    if (color.isValid()) {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}


void Widget::on_pushButton_sel_font_clicked()
{
    QFont iniFont = ui->plainTextEdit->font();
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, iniFont);
    if (ok)
        ui->plainTextEdit->setFont(font);
}


