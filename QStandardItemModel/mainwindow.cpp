#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>

const int FixedColumnCount = 6;
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    theModel     = new QStandardItemModel(2, FixedColumnCount, this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);

    label_current_file_ = new QLabel("current file:");
    label_current_file_->setMinimumWidth(250);
    label_cell_text_ = new QLabel("unknown");
    label_cell_text_->setMinimumWidth(200);
    label_cell_pos_ = new QLabel("unselected");
    label_cell_pos_->setMinimumWidth(100);

    ui->statusbar->addWidget(label_current_file_);
    ui->statusbar->addWidget(label_cell_text_);
    ui->statusbar->addWidget(label_cell_pos_);

    connect(
        theSelection, &QItemSelectionModel::currentChanged, this, &MainWindow::on_currentChanged);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
    connect(ui->action_append, &QAction::triggered, this, &MainWindow::onActionAppendTriggered);
    connect(ui->action_delete, &QAction::triggered, this, &MainWindow::onActionDeleteTriggered);
    connect(ui->action_left, &QAction::triggered, this, &MainWindow::onActionAlignLeftTriggered);
    connect(ui->action_blod, &QAction::triggered, this, &MainWindow::onActionAlignBoldTriggered);
    connect(ui->action_modeldata, &QAction::triggered, this, &MainWindow::onActionPreviewTriggered);
    connect(ui->action_save, &QAction::triggered, this, &MainWindow::onActionSaveTriggered);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_currentChanged(const QModelIndex &current, const QModelIndex &previous) {
    if (current.isValid()) {
        label_cell_pos_->setText(
            QString::asprintf("current pos:%d-%d", current.row(), current.column()));
        auto item = theModel->itemFromIndex(current);
        label_cell_text_->setText("text:" + item->text());
        QFont font = item->font();
        ui->action_blod->setChecked(font.bold());
    }
}

void MainWindow::onActionOpenTriggered() {
    QString curPath   = QCoreApplication::applicationDirPath();
    QString aFileName = QFileDialog::getOpenFileName(
        this, "open one file", curPath, "data file(*.txt); allfile(*.*)");
    if (aFileName.isEmpty())
        return;

    QStringList fFileContent;
    QFile       aFile(aFileName);
    if (aFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream aStream(&aFile);
        ui->plainTextEdit->clear();
        while (!aStream.atEnd()) {
            QString str = aStream.readLine();
            ui->plainTextEdit->appendPlainText(str);
            fFileContent.append(str);
        }
        aFile.close();
        this->label_current_file_->setText("current file:" + aFileName);
        initModelFromStringList(fFileContent);
    }
}

void MainWindow::initModelFromStringList(QStringList &aFileContent) {
    int rowCnt = aFileContent.count();
    theModel->setRowCount(rowCnt - 1);
    QString     header     = aFileContent.at(0);
    QStringList headerList = header.split(QRegExp("\\s+"), QString::SkipEmptyParts);
    theModel->setHorizontalHeaderLabels(headerList);

    QStandardItem *aItem;
    QStringList    tmpList;
    int            j;
    for (int i = 1; i < rowCnt; ++i) {
        QString aLineText = aFileContent.at(i);
        tmpList           = aLineText.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        for (j = 0; j < FixedColumnCount - 1; ++j) {
            aItem = new QStandardItem(tmpList.at(j));
            theModel->setItem(i - 1, j, aItem);
        }

        aItem = new QStandardItem(tmpList.at(j));
        aItem->setCheckable(true);
        if (tmpList.at(j) == "0")
            aItem->setCheckState(Qt::Unchecked);
        else
            aItem->setCheckState(Qt::Checked);
        theModel->setItem(i - 1, j, aItem);
    }
}

void MainWindow::onActionAppendTriggered() {
    QList<QStandardItem *> aItemList;
    QStandardItem *        aItem;
    for (int i = 0; i < FixedColumnCount - 1; ++i) {
        aItem = new QStandardItem("0");
        aItemList << aItem;
    }
    QString str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole)
                      .toString();
    aItem = new QStandardItem(str);
    aItem->setCheckable(true);
    aItemList << aItem;

    theModel->insertRow(theModel->rowCount(), aItemList);
    QModelIndex index = theModel->index(theModel->rowCount() - 1, 0);
    theSelection->clearSelection();
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select);
}

void MainWindow::onActionDeleteTriggered() {
    const QModelIndex current_index = theSelection->currentIndex();
    if (current_index.row() == theModel->rowCount() - 1) {
        theModel->removeRow(current_index.row());
    } else {
        theModel->removeRow(current_index.row());
        theSelection->setCurrentIndex(current_index, QItemSelectionModel::Select);
    }
}

void MainWindow::onActionAlignLeftTriggered() {
    if (!theSelection->hasSelection())
        return;

    QModelIndexList indexs = theSelection->selectedIndexes();
    for (int i = 0; i < indexs.count(); ++i) {
        QModelIndex    index = indexs.at(i);
        QStandardItem *item  = theModel->itemFromIndex(index);
        item->setTextAlignment(Qt::AlignLeft);
    }
}

void MainWindow::onActionAlignBoldTriggered() {
    if (!theSelection->hasSelection())
        return;

    QModelIndexList indexs = theSelection->selectedIndexes();
    for (int i = 0; i < indexs.count(); ++i) {
        QModelIndex    index = indexs.at(i);
        QStandardItem *item  = theModel->itemFromIndex(index);
        QFont          font  = item->font();
        font.setBold(true);
        item->setFont(font);
    }
}

void MainWindow::onActionPreviewTriggered() {
    ui->plainTextEdit->clear();
    QString str;

    int            i{}, j{};
    QStandardItem *item{};
    for (j = 0; j < theModel->columnCount(); ++j) {
        item = theModel->horizontalHeaderItem(j);
        str  = str + item->text() + "\t\t";
    }
    ui->plainTextEdit->appendPlainText(str);
    for (i = 0; i < theModel->rowCount(); ++i) {
        str.clear();
        for (j = 0; j < theModel->columnCount() - 1; ++j) {
            item = theModel->item(i, j);
            str += item->text() + "\t\t";
        }
        item = theModel->item(i, j);
        if (item->checkState() == Qt::Checked)
            str += "1";
        else
            str += "0";
        ui->plainTextEdit->appendPlainText(str);
    }
}

void MainWindow::onActionSaveTriggered() {
    QString current_path = QCoreApplication::applicationDirPath();
    QString aFileName    = QFileDialog::getSaveFileName(
        this, "please select one file", current_path, "data(*.txt);all data(*.*)");
    if (aFileName.isEmpty())
        return;

    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate))
        return;

    QTextStream    aStream(&aFile);
    QStandardItem *aItem;
    int            i, j;
    QString        str;
    ui->plainTextEdit->clear();
    for (i = 0; i < theModel->columnCount(); ++i) {
        aItem = theModel->horizontalHeaderItem(i);
        str   = str + aItem->text() + "\t\t";
    }
    aStream << str << "\n";
    ui->plainTextEdit->appendPlainText(str);
    for (i = 0; i < theModel->rowCount(); ++i) {
        str = "";
        for (j = 0; j < theModel->columnCount() - 1; ++j) {
            aItem = theModel->item(i, j);
            str   = str + aItem->text() + QString::asprintf("\t\t");
        }
        aItem = theModel->item(i, j);
        if (aItem->checkState() == Qt::Checked)
            str += "1";
        else
            str += "0";
        ui->plainTextEdit->appendPlainText(str);
        aStream << str << "\n";
    }
    aFile.close();
}
