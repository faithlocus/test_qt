#include "mainwindow.h"
#include "ui_mainwindow.h"

const int FixedColumnCount = 3;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    theModel = new QStandardItemModel(2, FixedColumnCount, this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    connect(theSelection,
            &QItemSelectionModel::currentChanged,
            this,
            &MainWindow::on_currentChanged);
    label_current_file_ = new QLabel("current file:");
    label_current_file_->setMinimumWidth(250);
    label_cell_text_ = new QLabel("unknown");
    label_cell_text_->setMinimumWidth(200);
    label_cell_pos_ = new QLabel("unselected");
    label_cell_pos_->setMinimumWidth(100);

    ui->statusbar->addWidget(label_current_file_);
    ui->statusbar->addWidget(label_cell_text_);
    ui->statusbar->addWidget(label_cell_pos_);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    if (current.isValid()) {
        label_cell_pos_->setText(
            QString::asprintf("current pos:%d-%d", current.row(), current.column()));
        auto item = theModel->itemFromIndex(current);
        label_cell_text_->setText("text:" + item->text());
        QFont font = item->font();
        ui->action_blod->setChecked(font.bold());
    }

}

