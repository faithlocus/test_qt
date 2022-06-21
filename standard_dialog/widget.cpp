#include "widget.h"
#include "ui_widget.h"
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QLineEdit>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_pushButton_clear_clicked() {
    ui->plainTextEdit->clear();
}

void Widget::on_pushButton_open_clicked() {
    QString curPath   = QDir::currentPath();
    QString dlgTitle  = "select one file";
    QString filter    = "text file(*.txt);;pic file(*.jpg *.gif);;all files(*.*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::on_pushButton_opens_clicked() {
    QString     curPath    = QDir::currentPath();
    QString     dlgTitle   = "select one file";
    QString     filter     = "text file(*.txt);;pic file(*.jpg *.gif);;all files(*.*)";
    QStringList aFileNames = QFileDialog::getOpenFileNames(this, dlgTitle, curPath, filter);
    for (QString filename : aFileNames)
        ui->plainTextEdit->appendPlainText(filename);
}

void Widget::on_pushButton_sel_folder_clicked() {
    QString curPath  = QCoreApplication::applicationDirPath();
    QString dlgTitle = "select one dir";
    QString selectDir =
        QFileDialog::getExistingDirectory(this, dlgTitle, curPath, QFileDialog::ShowDirsOnly);
    if (!selectDir.isEmpty())
        ui->plainTextEdit->appendPlainText(selectDir);
}

void Widget::on_pushButton_save_clicked() {
    QString curPath   = QCoreApplication::applicationDirPath();
    QString dlgTitle  = "save file";
    QString filter    = "h file(*.h);;cpp file(*.cpp);;all file(*.*)";
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);
    if (!aFileName.isEmpty())
        ui->plainTextEdit->appendPlainText(aFileName);
}

void Widget::on_pushButton_sel_color_clicked() {
    QPalette pal      = ui->plainTextEdit->palette();
    QColor   iniColor = pal.color(QPalette::Text);
    auto     color    = QColorDialog::getColor(iniColor, this, "save color");
    if (color.isValid()) {
        pal.setColor(QPalette::Text, color);
        ui->plainTextEdit->setPalette(pal);
    }
}

void Widget::on_pushButton_sel_font_clicked() {
    QFont iniFont = ui->plainTextEdit->font();
    bool  ok      = false;
    QFont font    = QFontDialog::getFont(&ok, iniFont);
    if (ok)
        ui->plainTextEdit->setFont(font);
}

void Widget::on_pushButton_input_str_clicked() {
    QString             dlgTitle     = "input work widget";
    QString             txtLable     = "input file name";
    QString             defaultInput = "new file.txt";
    QLineEdit::EchoMode echoMode     = QLineEdit::Normal;
    //    QLineEdit::EchoMode echoMode = QLineEdit::Password;
    bool    ok   = false;
    QString text = QInputDialog::getText(this, dlgTitle, txtLable, echoMode, defaultInput, &ok);
    if (ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}

void Widget::on_pushButton_input_int_clicked() {
    QString dlgTile      = "input work widget";
    QString txtLable     = "input file name";
    int     defaultValue = ui->plainTextEdit->font().pointSize();
    int     minValue = 6, maxValue = 50, stepValue = 1;
    bool    ok         = false;
    int     inputValue = QInputDialog::getInt(
        this, dlgTile, txtLable, defaultValue, minValue, maxValue, stepValue, &ok);
    if (ok) {
        QFont font = ui->plainTextEdit->font();
        font.setPointSize(inputValue);
        ui->plainTextEdit->setFont(font);
    }
}

void Widget::on_pushButton_input_double_clicked() {
    QString dlgTile      = "input work widget";
    QString txtLable     = "input file name";
    double  defaultValue = 3.3;
    double  minValue = 0, maxValue = 50;
    int     decimal    = 2;
    bool    ok         = false;
    double  inputValue = QInputDialog::getDouble(
        this, dlgTile, txtLable, defaultValue, minValue, maxValue, decimal, &ok);
    if (ok) {
        ui->plainTextEdit->appendPlainText(QString("%1").arg(inputValue));
    }
}

void Widget::on_pushButton_input_item_clicked() {
    QString     dlgTitle = "items dialog";
    QString     txtLable = "please";
    int         curIndex = 1;
    bool        editable = false;
    bool        ok       = false;
    QStringList items;
    items << "bj"
          << "sh"
          << "tj"
          << "cq";
    QString text = QInputDialog::getItem(this, dlgTitle, txtLable, items, curIndex, editable, &ok);
    if (ok && !text.isEmpty())
        ui->plainTextEdit->appendPlainText(text);
}
