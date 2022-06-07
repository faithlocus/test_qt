#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setActionForButton();
    createSelectionPopMenu();
    initSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setActionForButton()
{
    ui->toolButton_init->setDefaultAction(ui->action_init);
    ui->toolButton_clear->setDefaultAction(ui->action_clear);
    ui->toolButton_append->setDefaultAction(ui->action_append);
    ui->toolButton_insert->setDefaultAction(ui->action_insert);
    ui->toolButton_delete->setDefaultAction(ui->action_delete);

    ui->toolButton_all->setDefaultAction(ui->action_select_all);
    ui->toolButton_none->setDefaultAction(ui->action_select_none);
    ui->toolButton_inverse->setDefaultAction(ui->action_select_inverse);
}

void MainWindow::createSelectionPopMenu()
{
    // 创建下拉菜单
    QMenu *menu = new QMenu(this);
    menu->addAction(ui->action_select_all);
    menu->addAction(ui->action_select_none);
    menu->addAction(ui->action_select_inverse);

    // listwidget上方的toolbutton
    ui->toolButton_select_item->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolButton_select_item->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolButton_select_item->setDefaultAction(ui->action_select_popmenu);
    ui->toolButton_select_item->setMenu(menu);

    // 工具栏的toolbutton
    QToolButton *btn = new QToolButton(this);
    btn->setPopupMode(QToolButton::InstantPopup);
    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    btn->setDefaultAction(ui->action_select_popmenu);
    btn->setMenu(menu);
    ui->toolBar->addWidget(btn);

    ui->toolBar->addSeparator();
    ui->toolBar->addAction(ui->action_quit);
}

void MainWindow::initSignalSlots()
{
    connect(ui->action_init, &QAction::triggered, this, &MainWindow::onActionListInitTriggered);
    connect(ui->action_insert, &QAction::triggered, this, &MainWindow::onActionInsertTriggered);
    connect(ui->action_clear, &QAction::triggered, this, &MainWindow::onActionClearTriggered);
    connect(ui->action_delete, &QAction::triggered, this, &MainWindow::onActionDeleteTriggered);
    connect(ui->action_select_all, &QAction::triggered, this, &MainWindow::onActionSelectAll);
    connect(ui->action_select_none, &QAction::triggered, this, &MainWindow::onActionSelectNone);
    connect(ui->action_select_inverse,
            &QAction::triggered,
            this,
            &MainWindow::onActionSelectInverse);
    connect(ui->listWidget,
            &QListWidget::currentItemChanged,
            this,
            &MainWindow::onListwidgetCurrentItemChanged);
    connect(ui->listWidget,
            &QListWidget::customContextMenuRequested,
            this,
            &MainWindow::onListwidgetCustomContextMenuRequested);
}

void MainWindow::onActionListInitTriggered()
{
    QListWidgetItem *item;
    QIcon icon;
    icon.addFile(":/icons/icons/check2.ico");
    bool checked = ui->checkBox->isChecked();

    ui->listWidget->clear();
    for (int i = 0; i < 10; ++i) {
        QString str = QString::asprintf("item %d", i);
        item = new QListWidgetItem();
        item->setText(str);
        item->setIcon(icon);
        item->setCheckState(Qt::Checked);

        if (checked)
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable
                           | Qt::ItemIsEnabled);
        else
            item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

        ui->listWidget->addItem(item);
    }
}

void MainWindow::onActionInsertTriggered()
{
    QListWidgetItem *item = new QListWidgetItem("New Inserted Item");
    item->setCheckState(Qt::Checked);

    QIcon icon;
    icon.addFile(":/icons/icons/check2.ico");
    item->setIcon(icon);

    bool checked = ui->checkBox->isChecked();
    if (checked)
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable
                       | Qt::ItemIsEnabled);
    else
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

    //        ui->listWidget->addItem(item);
    ui->listWidget->insertItem(ui->listWidget->count(), item);
}

void MainWindow::onActionClearTriggered()
{
    ui->listWidget->clear();
}

void MainWindow::onActionDeleteTriggered()
{
    int row = ui->listWidget->currentRow();
    auto item = ui->listWidget->takeItem(row);
    delete item;
}

void MainWindow::onActionSelectAll()
{
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        item->setCheckState(Qt::Checked);
    }
}

void MainWindow::onActionSelectNone()
{
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        item->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::onActionSelectInverse()
{
    int count = ui->listWidget->count();
    for (int i = 0; i < count; ++i) {
        QListWidgetItem *item = ui->listWidget->item(i);
        item->setCheckState((Qt::Checked == item->checkState()) ? Qt::Unchecked : Qt::Checked);
    }
}

void MainWindow::onListwidgetCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QString cur, pre;
    if (current)
        cur += QString("cur:") += current->text();

    if (previous)
        pre += QString("pre:") += previous->text();

    ui->lineEdit_2->setText(pre + cur);
}

void MainWindow::onListwidgetCustomContextMenuRequested(const QPoint &pos)
{
    Q_UNUSED(pos);
    QMenu *menu_list = new QMenu(this);
    menu_list->addAction(ui->action_init);
    menu_list->addAction(ui->action_clear);
    menu_list->addAction(ui->action_insert);
    menu_list->addAction(ui->action_append);
    menu_list->addAction(ui->action_delete);

    menu_list->addSeparator();
    menu_list->addAction(ui->action_select_all);
    menu_list->addAction(ui->action_select_none);
    menu_list->addAction(ui->action_select_inverse);
    menu_list->exec(QCursor::pos());
    delete menu_list;
}
