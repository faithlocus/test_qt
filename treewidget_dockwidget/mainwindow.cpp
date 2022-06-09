#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label_file_name_ = new QLabel("image_file_path");
    ui->statusbar->addWidget(label_file_name_);
    setCentralWidget(ui->scrollArea);
    initTree();
    initSignalSlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTree()
{
    ui->treeWidget->clear();
    QString data_str;
    QIcon icon;
    //    icon.addFile(":/icons/icons/check2.ico");
    icon.addFile(":/icons/icons/open3.bmp");

    QTreeWidgetItem *item = new QTreeWidgetItem(MainWindow::kTopItem);
    item->setIcon(MainWindow::kColItem, icon);
    item->setText(MainWindow::kColItem, "图片文件");
    item->setText(MainWindow::kColType, "type = kTopItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled
                   | Qt::ItemIsAutoTristate);

    item->setCheckState(kColItem, Qt::Checked);
    item->setData(MainWindow::kColItem, Qt::UserRole, QVariant(data_str));
    ui->treeWidget->addTopLevelItem(item);
}

void MainWindow::initSignalSlot()
{
    connect(ui->action_add_folder,
            &QAction::triggered,
            this,
            &MainWindow::onActionAddFolderTriggered);
    connect(ui->action_add_file, &QAction::triggered, this, &MainWindow::onActionAddFilesTriggered);
    connect(ui->treeWidget,
            &QTreeWidget::currentItemChanged,
            this,
            &MainWindow::onCurrentItemChanged);
    connect(ui->action_delete_item,
            &QAction::triggered,
            this,
            &MainWindow::onActionDeleteItemTriggered);
    connect(ui->action_scan_items,
            &QAction::triggered,
            this,
            &MainWindow::onActionScanItemsTriggered);
    connect(ui->action_fith, &QAction::triggered, this, &MainWindow::onActionFitHTriggered);
    connect(ui->action_fitw, &QAction::triggered, this, &MainWindow::onActionFitWTriggered);
    connect(ui->action_zoomin, &QAction::triggered, this, &MainWindow::onActionZoomInTriggered);
}

void MainWindow::onActionAddFolderTriggered()
{
    QString dir = QFileDialog::getExistingDirectory();
    if (!dir.isEmpty()) {
        QTreeWidgetItem *par_item = ui->treeWidget->currentItem();
        addFolderItem(par_item, dir);
    }
}

void MainWindow::addFolderItem(QTreeWidgetItem *par_item, QString dir_name)
{
    QIcon icon(":/icons/icons/open3.bmp");
    QString node_text = getFinalFolderName(dir_name);
    QTreeWidgetItem *item = new QTreeWidgetItem(MainWindow::kGroupItem);
    item->setIcon(MainWindow::kColItem, icon);
    item->setText(MainWindow::kColItem, node_text);
    item->setText(MainWindow::kColType, "type = kGroupItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled
                   | Qt::ItemIsAutoTristate);
    item->setCheckState(kColItem, Qt::Checked);
    item->setData(kColItem, Qt::UserRole, QVariant(dir_name));
    par_item->addChild(item);
}

QString MainWindow::getFinalFolderName(const QString &path_name)
{
    int cnt = path_name.length();
    int i = path_name.lastIndexOf("/");
    QString str = path_name.right(cnt - i - 1);
    return str;
}

void MainWindow::onActionAddFilesTriggered()
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      "选择一个或多个文件",
                                                      "",
                                                      "Images(*.jpg)");
    if (files.isEmpty())
        return;
    QTreeWidgetItem *par_item, *item;
    item = ui->treeWidget->currentItem();
    if (item->type() == kImageItem)
        par_item = item->parent();
    else
        par_item = item;

    for (int i = 0; i < files.size(); ++i) {
        QString file_name = files.at(i);
        addImageItem(par_item, file_name);
    }
}


void MainWindow::addImageItem(QTreeWidgetItem *par_item, QString file_name)
{
    QIcon icon(":/icons/icons/101.bmp");
    QString node_text = getFinalFolderName(file_name);
    QTreeWidgetItem *item = new QTreeWidgetItem(kImageItem);
    item->setIcon(kColItem, icon);
    item->setText(kColItem, node_text);
    item->setText(kColType, "type = kImageItem");
    item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled
                   | Qt::ItemIsAutoTristate);

    item->setCheckState(kColItem, Qt::Checked);
    item->setData(kColItem, Qt::UserRole, QVariant(file_name));
    par_item->addChild(item);
}

void MainWindow::onCurrentItemChanged(QTreeWidgetItem *cur, QTreeWidgetItem *pre)
{
    Q_UNUSED(pre)
    if (!cur)
        return;
    int var = cur->type();
    switch (var) {
    case kTopItem:
        ui->action_add_file->setEnabled(true);
        ui->action_add_folder->setEnabled(true);
        ui->action_delete_item->setEnabled(false);
        break;
    case kGroupItem:
        ui->action_add_file->setEnabled(true);
        ui->action_add_folder->setEnabled(true);
        ui->action_delete_item->setEnabled(true);
        break;
    case kImageItem:
        ui->action_add_folder->setEnabled(false);
        ui->action_add_file->setEnabled(true);
        ui->action_delete_item->setEnabled(true);
        displayImage(cur);
        break;
    default:
        break;
    }
}

void MainWindow::onActionDeleteItemTriggered()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QTreeWidgetItem *par = item->parent();
    par->removeChild(item);
    delete item;
}

void MainWindow::onActionScanItemsTriggered()
{
    for (int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);
        changeItemCaption(item);
    }
}

void MainWindow::changeItemCaption(QTreeWidgetItem *item)
{
    QString str = "*" + item->text(kColItem);
    item->setText(kColItem, str);
    if (item->childCount() > 0)
        for (int i = 0; i < item->childCount(); ++i)
            changeItemCaption(item->child(i));
}

void MainWindow::displayImage(QTreeWidgetItem *item)
{
    QString file_name = item->data(kColItem, Qt::UserRole).toString();
    label_file_name_->setText(file_name);
    cur_pixmap_.load(file_name);
    onActionFitHTriggered();
}

void MainWindow::onActionFitHTriggered()
{
    int h = ui->scrollArea->height();
    int realh = cur_pixmap_.height();
    pix_ratio_ = float(h) / realh;
    QPixmap pix = cur_pixmap_.scaledToHeight(h - 30);
    ui->label->setPixmap(pix);
}

void MainWindow::onActionFitWTriggered()
{
    int w = ui->scrollArea->width();
    int realw = cur_pixmap_.width();
    pix_ratio_ = float(w) / realw;
    QPixmap pix = cur_pixmap_.scaledToWidth(w - 30);
    ui->label->setPixmap(pix);
}

void MainWindow::onActionZoomInTriggered()
{
    pix_ratio_ = pix_ratio_ / 2;
    int w = pix_ratio_ * cur_pixmap_.width();
    int h = pix_ratio_ * cur_pixmap_.height();
    QPixmap pix = cur_pixmap_.scaled(w, h);
    ui->label->setPixmap(pix);
}
