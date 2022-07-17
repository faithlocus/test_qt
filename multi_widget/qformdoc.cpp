#include "qformdoc.h"
#include "ui_qformdoc.h"
#include <QMessageBox>
#include <QToolBar>
#include <QVBoxLayout>

QFormDoc::QFormDoc(QWidget *parent) : QWidget(parent), ui(new Ui::QFormDoc) {
    ui->setupUi(this);
    QToolBar *locToolBar = new QToolBar("文档", this);
    locToolBar->addAction(ui->action_open);
    locToolBar->addAction(ui->action_font);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->action_cut);
    locToolBar->addAction(ui->action_copy);
    locToolBar->addAction(ui->action_paste);
    locToolBar->addAction(ui->action_undo);
    locToolBar->addAction(ui->action_redo);
    locToolBar->addSeparator();
    locToolBar->addAction(ui->action_close);
    locToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QVBoxLayout *Layout = new QVBoxLayout(this);
    Layout->addWidget(locToolBar);
    Layout->addWidget(ui->plainTextEdit);
    Layout->setContentsMargins(2, 2, 2, 2);
    Layout->setSpacing(2);
    this->setLayout(Layout);
}

QFormDoc::~QFormDoc() {
    QMessageBox::information(this, "消息", "QFormDoc对象被删除和释放");
    delete ui;
}
