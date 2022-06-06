#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMap>
#include <QDebug>
#include <QTextDocument>
#include <QTextBlock>

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


void MainWindow::on_pushButton_init_clicked()
{
    ui->comboBox->clear();
    //    QStringList items;
    //    items << "北京"
    //          << "上海"
    //          << "重庆"
    //          << "天津";
    //    ui->comboBox->addItems(items);
    //    return;
    QIcon icon;
    icon.addFile(":/image/pic/北京.ico");
    for (int i = 0; i < 20; ++i) {
        ui->comboBox->addItem(icon, QString::asprintf("item %d", i));
        //        ui->comboBox->addItem(QString::asprintf("item %d", i));
    }
}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->comboBox->clear();
}


void MainWindow::on_pushButton_init_2_clicked()
{
    QMap<QString, int> city_zone;
    city_zone.insert("北京", 10);
    city_zone.insert("上海", 11);
    city_zone.insert("天津", 12);
    city_zone.insert("重庆", 13);
    ui->comboBox_2->clear();
    foreach (const QString &str, city_zone.keys())
        ui->comboBox_2->addItem(str, city_zone.value(str));

    int count = ui->comboBox_2->count();
    for (int i = 0; i < count; ++i) {
        qDebug() << ui->comboBox_2->itemData(i);
    }
}


void MainWindow::on_checkBox_editable_stateChanged(int arg1)
{
    ui->comboBox->setEditable(arg1);
}


void MainWindow::on_pushButton_clicked()
{
    //    auto str = ui->plainTextEdit->toPlainText();
    QTextDocument *document = ui->plainTextEdit->document();
    auto count = document->blockCount();
    QIcon icon(":/image/pic/北京.ico");
    for (int i = 0; i < count; ++i) {
        QTextBlock text_block = document->findBlockByNumber(i);
        QString str = text_block.text();
        ui->comboBox->addItem(icon, str);
    }
}

