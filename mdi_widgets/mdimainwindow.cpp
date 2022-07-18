#include "mdimainwindow.h"
#include "qformdoc.h"
#include "ui_mdimainwindow.h"

#include "qformdoc.h"
#include <QDir>
#include <QFileDialog>

MDIMainWindow::MDIMainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MDIMainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->mdiArea);
    setWindowState(Qt::WindowMaximized);
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

MDIMainWindow::~MDIMainWindow() {
    delete ui;
}

void MDIMainWindow::on_action_new_triggered() {
    QFormDoc *formdoc = new QFormDoc(this);
    ui->mdiArea->addSubWindow(formdoc);
    formdoc->show();

    ui->action_cut->setEnabled(true);
    ui->action_copy->setEnabled(true);
    ui->action_paste->setEnabled(true);
    ui->action_font->setEnabled(true);
}

void MDIMainWindow::on_action_open_triggered() {
    bool      need_new{ false };
    QFormDoc *formdoc;
    if (ui->mdiArea->subWindowList().count() > 0) {
        formdoc  = ( QFormDoc * )ui->mdiArea->activeSubWindow()->widget();
        need_new = formdoc->isFileOpened();
    } else {
        need_new = true;
    }

    QString cur_path  = QDir::currentPath();
    QString file_name = QFileDialog::getOpenFileName(
        this, "打开一个文件", cur_path, "C程序文件(*.h *.cpp);;所有文件(*.*)");
    if (file_name.isEmpty())
        return;

    if (need_new) {
        formdoc = new QFormDoc(this);
        ui->mdiArea->addSubWindow(formdoc);
    }

    formdoc->loadFromFile(file_name);
    formdoc->show();
    ui->action_cut->setEnabled(true);
    ui->action_copy->setEnabled(true);
    ui->action_paste->setEnabled(true);
    ui->action_font->setEnabled(true);
}

void MDIMainWindow::on_action_mdi_triggered(bool checked) {
    if (checked) {
        ui->mdiArea->setViewMode(QMdiArea::TabbedView);
        ui->mdiArea->setTabsClosable(true);
        ui->action_cascade->setEnabled(false);
        ui->action_tile->setEnabled(false);
    } else {
        ui->mdiArea->setViewMode(QMdiArea::SubWindowView);
        ui->action_cascade->setEnabled(true);
        ui->action_tile->setEnabled(true);
    }
}

void MDIMainWindow::on_action_cascade_triggered() {
    ui->mdiArea->cascadeSubWindows();
}

void MDIMainWindow::on_action_tile_triggered() {
    ui->mdiArea->tileSubWindows();
}

void MDIMainWindow::on_action_close_all_triggered() {
    ui->mdiArea->closeAllSubWindows();
}

void MDIMainWindow::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1) {
    Q_UNUSED(arg1);
    if (ui->mdiArea->subWindowList().count() == 0) {
        ui->action_cut->setEnabled(false);
        ui->action_copy->setEnabled(false);
        ui->action_paste->setEnabled(false);
        ui->action_font->setEnabled(false);
        ui->statusbar->clearMessage();
    } else {
        QFormDoc *formdoc = ( QFormDoc * )ui->mdiArea->activeSubWindow()->widget();
        ui->statusbar->showMessage(formdoc->currentFileName());
    }
}

void MDIMainWindow::on_action_cut_triggered() {
    QFormDoc *formdoc = ( QFormDoc * )ui->mdiArea->activeSubWindow()->widget();
    formdoc->textCut();
}

void MDIMainWindow::on_action_font_triggered() {
    QFormDoc *formdoc = ( QFormDoc * )ui->mdiArea->activeSubWindow()->widget();
    formdoc->setEditFont();
}
