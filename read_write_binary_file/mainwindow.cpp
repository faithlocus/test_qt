#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
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
