#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->tabWidget);
    theModel = new QStandardItemModel(2, FixedColumnCount, this);
    theSelection = new QItemSelectionModel(theModel);
    ui->tableView->setModel(theModel);
    ui->tableView->setSelectionModel(theSelection);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_action_save_stm_triggered() {
    QString curPath = QDir::currentPath();
    QString aFileName =
        QFileDialog::getSaveFileName(this, "选择保存文件", curPath, "Qt预定义编码文件(*.stm)");
    if (aFileName.isEmpty())
        return;
    if (saveDataAsStream(aFileName))
        QMessageBox::information(this, "提示消息", "文件已经保存成功");
}

bool MainWindow::saveDataAsStream(QString &aFileName) {
    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::WriteOnly | QIODevice::Truncate)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_12);
    qint16 rowCount = theModel->rowCount();
    qint16 colCount = theModel->columnCount();
    aStream << rowCount << colCount;

    for (int i = 0; i < colCount; ++i)
        aStream << theModel->horizontalHeaderItem(i)->text();

    for (int j = 0; j < rowCount; ++j) {
        QStandardItem *item   = theModel->item(j, 0);
        qint16         ceshen = item->data(Qt::DisplayRole).toInt();
        aStream << ceshen;

        item           = theModel->item(j, 1);
        qreal chuishen = item->data(Qt::DisplayRole).toFloat();
        aStream << chuishen;

        item          = theModel->item(j, 2);
        qreal fangwei = item->data(Qt::DisplayRole).toFloat();
        aStream << fangwei;

        item        = theModel->item(j, 3);
        qreal weiyi = item->data(Qt::DisplayRole).toFloat();
        aStream << weiyi;

        item             = theModel->item(j, 4);
        QString zhiliang = item->data(Qt::DisplayRole).toString();
        aStream << zhiliang;

        item        = theModel->item(j, 5);
        bool quyang = (item->checkState() == Qt::Checked);
        aStream << quyang;
    }
    aFile.close();
    return true;
}

void MainWindow::on_action_open_stm_triggered() {
    QString curPath = QDir::currentPath();
    QString aFileName =
        QFileDialog::getOpenFileName(this, "打开一个文件", curPath, "Qt预定义编码数据文件(*.stm)");
    if (aFileName.isEmpty())
        return;
    if (openDataAsStream(aFileName))
        QMessageBox::information(this, "提示消息", "文件已经打开");
}

bool MainWindow::openDataAsStream(QString &aFileName) {
    QFile aFile(aFileName);
    if (!(aFile.open(QIODevice::ReadOnly)))
        return false;
    QDataStream aStream(&aFile);
    aStream.setVersion(QDataStream::Qt_5_12);
    qint16 rowCount, colCount;
    aStream >> rowCount >> colCount;
    resetTable(rowCount);
    QString str;
    for (int i = 0; i < colCount; ++i)
        aStream >> str;
    qint16         ceshen;
    qreal          chuishen, fangwei, weiyi;
    QString        zhiliang;
    bool           quyang;
    QStandardItem *aItem;
    QModelIndex    index;
    for (int i = 0; i < rowCount; ++i) {
        aStream >> ceshen;
        index = theModel->index(i, 0);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(ceshen, Qt::DisplayRole);

        aStream >> chuishen;
        index = theModel->index(i, 1);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(chuishen, Qt::DisplayRole);

        aStream >> fangwei;
        index = theModel->index(i, 2);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(fangwei, Qt::DisplayRole);

        aStream >> weiyi;
        index = theModel->index(i, 3);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(weiyi, Qt::DisplayRole);

        aStream >> zhiliang;
        index = theModel->index(i, 4);
        aItem = theModel->itemFromIndex(index);
        aItem->setData(zhiliang, Qt::DisplayRole);

        aStream >> quyang;
        index = theModel->index(i, 5);
        if (quyang)
            aItem->setCheckState(Qt::Checked);
        else
            aItem->setCheckState(Qt::Unchecked);
    }
    aFile.close();
    return true;
}

void MainWindow::resetTable(int aRowCount) {
    theModel->removeRows(0, theModel->rowCount());
    theModel->setRowCount(aRowCount);
    QString str = theModel->headerData(theModel->columnCount() - 1, Qt::Horizontal, Qt::DisplayRole)
                      .toString();
    for (int i = 0; i < theModel->rowCount(); ++i) {
        QModelIndex    index = theModel->index(i, FixedColumnCount - 1);
        QStandardItem *aItem = theModel->itemFromIndex(index);
        aItem->setCheckable(true);
        aItem->setData(str, Qt::DisplayRole);
        aItem->setEditable(false);
    }
}

void MainWindow::on_action_open_dat_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getOpenFileName(this,
                                                     "select open file",
                                                     curPath,
                                                     "standard data file(*.dat)");
    if (aFileName.isEmpty())
        return;
    if (openBinaryFile(aFileName))
        QMessageBox::information(this, "information", "file had opened");
}

bool MainWindow::openBinaryFile(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::ReadOnly))
        return false;
    QDataStream aStream(&aFile);
    aStream.setByteOrder(QDataStream::LittleEndian);

    qint16 rowCount, colCount;
    aStream.readRawData((char *) &rowCount, sizeof(qint16));
    aStream.readRawData((char *) &colCount, sizeof(qint16));
    resetTable(rowCount);

    char *buf;
    uint strLen;
    for (int i = 0; i < colCount; ++i) {
        aStream.readBytes(buf, strLen);
        QString str = QString::fromLocal8Bit(buf, strLen);
    }

    QStandardItem *item;
    qint16 ceshen;
    qreal chuishen, fangwei, weiyi;
    QString zhiliang;
    qint8 quyang;
    QModelIndex index;
    for (int i = 0; i < rowCount; ++i) {
        aStream.readRawData((char *) &ceshen, sizeof(qint16));
        index = theModel->index(i, 0);
        item = theModel->itemFromIndex(index);
        item->setData(ceshen, Qt::DisplayRole);

        aStream.readRawData((char *) &chuishen, sizeof(qreal));
        index = theModel->index(i, 1);
        item = theModel->itemFromIndex(index);
        item->setData(chuishen, Qt::DisplayRole);

        aStream.readRawData((char *) &fangwei, sizeof(qreal));
        index = theModel->index(i, 2);
        item = theModel->itemFromIndex(index);
        item->setData(fangwei, Qt::DisplayRole);

        aStream.readRawData((char *) &weiyi, sizeof(qreal));
        index = theModel->index(i, 3);
        item = theModel->itemFromIndex(index);
        item->setData(weiyi, Qt::DisplayRole);

        aStream.readBytes(buf, strLen);
        zhiliang = QString::fromLocal8Bit(buf, strLen);
        index = theModel->index(i, 4);
        item = theModel->itemFromIndex(index);
        item->setData(zhiliang, Qt::DisplayRole);

        aStream.readRawData((char *) &quyang, sizeof(qint8));
        index = theModel->index(i, 5);
        item = theModel->itemFromIndex(index);
        if (quyang == 1)
            item->setCheckState(Qt::Checked);
        else
            item->setCheckState(Qt::Unchecked);
    }

    aFile.close();
    return true;
}

void MainWindow::on_action_save_dat_triggered()
{
    QString curPath = QDir::currentPath();
    QString aFileName = QFileDialog::getSaveFileName(this,
                                                     "select file",
                                                     curPath,
                                                     "standard data file(*.dat)");
    if (aFileName.isEmpty())
        return;
    if (saveBinaryFile(aFileName))
        QMessageBox::information(this, "information", "file had saved");
}

bool MainWindow::saveBinaryFile(QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly))
        return false;
    QDataStream aStream(&aFile);
    aStream.setByteOrder(QDataStream::LittleEndian);
    qint16 rowCount = theModel->rowCount();
    qint16 colCount = theModel->columnCount();
    aStream.writeRawData((char *) &rowCount, sizeof(qint16));
    aStream.writeRawData((char *) &colCount, sizeof(qint16));
    QByteArray btArray;
    QStandardItem *item;
    for (int i = 0; i < colCount; ++i) {
        item = theModel->horizontalHeaderItem(i);
        btArray = item->text().toUtf8();
        aStream.writeBytes(btArray, btArray.length());
    }

    qint8 yes = 1, no = 0;
    for (int i = 0; i < rowCount; ++i) {
        item = theModel->item(i, 0);
        qint16 ceshen = item->data(Qt::DisplayRole).toInt();
        aStream.writeRawData((char *) &ceshen, sizeof(qint16));

        item = theModel->item(i, 1);
        qint16 chuishen = item->data(Qt::DisplayRole).toInt();
        aStream.writeRawData((char *) &chuishen, sizeof(qint16));

        item = theModel->item(i, 2);
        qint16 fangwei = item->data(Qt::DisplayRole).toInt();
        aStream.writeRawData((char *) &fangwei, sizeof(qint16));

        item = theModel->item(i, 3);
        qint16 weiyi = item->data(Qt::DisplayRole).toInt();
        aStream.writeRawData((char *) &weiyi, sizeof(qint16));

        item = theModel->item(i, 4);
        QString zhiliang = item->data(Qt::DisplayRole).toString();
        btArray = zhiliang.toUtf8();
        aStream.writeBytes(btArray, btArray.length());

        item = theModel->item(i, 5);
        bool quyang = item->data(Qt::DisplayRole).toBool();
        if (quyang)
            aStream.writeRawData((char *) &yes, sizeof(qint8));
        else
            aStream.writeRawData((char *) &no, sizeof(qint8));
    }
    aFile.close();
    return true;
}

