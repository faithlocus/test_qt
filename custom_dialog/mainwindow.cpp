#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QCloseEvent>

#include "qwdialogsize.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , dlgheaders(nullptr)
    , dlglocate(nullptr)
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
    connect(ui->action_locate, &QAction::triggered, this, &MainWindow::onActionLocateTriggered);
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

void MainWindow::onActionLocateTriggered()
{
    setLocateEnable(false);
    dlglocate = new QWDialogLocate(this);
    dlglocate->setAttribute(Qt::WA_DeleteOnClose);
    Qt::WindowFlags flags = dlglocate->windowFlags();
    dlglocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint);

    dlglocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex index = theSelection->currentIndex();
    if (index.isValid())
        dlglocate->initSpinValue(index.row(), index.column());
    dlglocate->show();
}

void MainWindow::setACellText(int row, int column, QString text)
{
    QModelIndex index = theModel->index(row, column);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
    theModel->setData(index, text, Qt::DisplayRole);
}

void MainWindow::setLocateEnable(bool flag)
{
    ui->action_locate->setEnabled(flag);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if (dlglocate)
        dlglocate->initSpinValue(index.row(), index.column());
}

void MainWindow::setDlgLocatNull()
{
    dlglocate = nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this,
                                    "question",
                                    "are you want to quit?",
                                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                                    QMessageBox::No);
    if (ret == QMessageBox::Yes)
        event->accept();
    else
        event->ignore();
}
