#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model_ = new QFileSystemModel();
    model_->setRootPath(QDir::currentPath());
    ui->treeView->setModel(model_);
    ui->tableView->setModel(model_);
    ui->listView->setModel(model_);
    connect(ui->treeView, &QTreeView::clicked, ui->tableView, &QTableView::setRootIndex);
    connect(ui->treeView, &QTreeView::clicked, ui->listView, &QListView::setRootIndex);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    ui->checkBox_node->setChecked(model_->isDir(index));
    ui->label_path->setText(model_->filePath(index));
    ui->label_filename->setText(model_->fileName(index));
    ui->label_type->setText(model_->type(index));
    int sz = model_->size(index) / 1024;
    if (sz < 1024)
        ui->label_size->setText(QString("%1 KB").arg(sz));
    else
        ui->label_size->setText(QString("%1 MB").arg(sz / 1024));
}

