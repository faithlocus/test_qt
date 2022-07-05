#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qwdialogsize.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dlgheaders(nullptr)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(5, 4, this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    initSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initSignalSlots()
{
    connect(ui->action_count, &QAction::triggered, this, &MainWindow::onActionCountTriggered);
    connect(ui->action_headtext, &QAction::triggered, this, &MainWindow::onActionHeadersTriggered);
}

void MainWindow::onActionCountTriggered()
{
//    QWDialogSize *dlgTableSize = new QWDialogSize(this);
//    auto flags = dlgTableSize->windowFlags();
//    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
//    dlgTableSize->setRowColumn(theModel->rowCount(), theModel->columnCount());
//    int ret = dlgTableSize->exec();
//    if (ret == QDialog::Accepted) {
//        int rows = dlgTableSize->rowCount();
//        int cols = dlgTableSize->columnCount();
//        theModel->setRowCount(rows);
//        theModel->setColumnCount(cols);
//    }
//    delete dlgTableSize;
    QWDialogSize dlgTableSize(this);
    auto flags = dlgTableSize.windowFlags();
    dlgTableSize.setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint);
    dlgTableSize.setRowColumn(theModel->rowCount(), theModel->columnCount());
    int ret = dlgTableSize.exec();
    if (ret == QDialog::Accepted) {
        int rows = dlgTableSize.rowCount();
        int cols = dlgTableSize.columnCount();
        theModel->setRowCount(rows);
        theModel->setColumnCount(cols);
    }
}

void MainWindow::onActionHeadersTriggered()
{
    if (!dlgheaders)
        dlgheaders = new QWDialogHeaders(this);
    if (dlgheaders->headerList().count() != theModel->columnCount()) {
        QStringList strlist;
        for (int i = 0; i < theModel->columnCount(); ++i)
            strlist.append(theModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        dlgheaders->setHeaderList(strlist);
    }

    int ret = dlgheaders->exec();
    if (ret == QDialog::Accepted) {
        QStringList strList = dlgheaders->headerList();
        theModel->setHorizontalHeaderLabels(strList);
    }
}
