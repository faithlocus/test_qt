#include "qwdialogsize.h"
#include "ui_qwdialogsize.h"
#include <QMessageBox>

QWDialogSize::QWDialogSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogSize)
{
    ui->setupUi(this);
}

QWDialogSize::~QWDialogSize()
{
    QMessageBox::information(this, "info", "set row count, set column count will deleted");
    delete ui;
}


int QWDialogSize::rowCount() const
{
    return ui->spinBox_row->value();
}

int QWDialogSize::columnCount() const
{
    return ui->spinBox_column->value();
}

void QWDialogSize::setRowColumn(int row, int column)
{
    ui->spinBox_row->setValue(row);
    ui->spinBox_column->setValue(column);
}
