#include "qwdialogheaders.h"
#include "ui_qwdialogheaders.h"
#include <QMessageBox>

QWDialogHeaders::QWDialogHeaders(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogHeaders)
{
    ui->setupUi(this);
    model = new QStringListModel(this);
    ui->listView->setModel(model);
}

QWDialogHeaders::~QWDialogHeaders()
{
    QMessageBox::information(this, "info", "set column title dialog will deleted");
    delete ui;
}

void QWDialogHeaders::setHeaderList(QStringList &headers)
{
    model->setStringList(headers);
}

QStringList QWDialogHeaders::headerList() const
{
    return model->stringList();
}
