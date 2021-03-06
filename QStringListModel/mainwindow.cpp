#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList the_list;
    the_list << "北京"
             << "上海"
             << "天津"
             << "河北";
    model_ = new QStringListModel(this);
    model_->setStringList(the_list);
    ui->listView->setModel(model_);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked
                                  | QAbstractItemView::SelectedClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_add_clicked()
{
    model_->insertRow(model_->rowCount());
    auto index = model_->index(model_->rowCount() - 1, 0);
    model_->setData(index, "new item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}


void MainWindow::on_pushButton_insert_clicked()
{
    auto index = ui->listView->currentIndex();
    model_->insertRow(index.row());
    model_->setData(index, "insert item", Qt::DisplayRole);
    ui->listView->setCurrentIndex(index);
}



void MainWindow::on_pushButton_delete_clicked()
{
    auto index = ui->listView->currentIndex();
    model_->removeRow(index.row());
}



void MainWindow::on_pushButton_clearlist_clicked()
{
    model_->removeRows(0, model_->rowCount());
}


void MainWindow::on_pushButton_cleartext_clicked()
{
    ui->plainTextEdit->clear();
}


void MainWindow::on_pushButton_show_clicked()
{
    QStringList tmp_list = model_->stringList();
    ui->plainTextEdit->clear();
    for (int i = 0; i < tmp_list.count(); ++i) {
        ui->plainTextEdit->appendPlainText(tmp_list.at(i));
    }
}


void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    ui->label->setText(QString::asprintf("当前项：row=%d, column=%d", index.row(), index.column()));
}

