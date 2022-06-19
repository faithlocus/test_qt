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

    connect(
        theSelection, &QItemSelectionModel::currentChanged, this, &MainWindow::on_currentChanged);
    label_current_file_ = new QLabel("current file:");
    label_current_file_->setMinimumWidth(250);
    label_cell_text_ = new QLabel("unknown");
    label_cell_text_->setMinimumWidth(200);
    label_cell_pos_ = new QLabel("unselected");
    label_cell_pos_->setMinimumWidth(100);

    ui->statusbar->addWidget(label_current_file_);
    ui->statusbar->addWidget(label_cell_text_);
    ui->statusbar->addWidget(label_cell_pos_);
    connect(ui->action_open, &QAction::triggered, this, &MainWindow::onActionOpenTriggered);
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
