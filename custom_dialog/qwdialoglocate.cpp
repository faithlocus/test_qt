#include "qwdialoglocate.h"
#include "ui_qwdialoglocate.h"

#include <QMessageBox>

QWDialogLocate::QWDialogLocate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QWDialogLocate)
{
    ui->setupUi(this);
    connect(ui->pushButton_set, &QPushButton::clicked, this, &QWDialogLocate::on_btnSetText_clicked);
}

QWDialogLocate::~QWDialogLocate()
{
    QMessageBox::information(this, "info", "locate dialog will deleted");
    delete ui;
}

void QWDialogLocate::showEvent(QShowEvent *event)
{
    emit changeActionEnable(false);
}
void QWDialogLocate::closeEvent(QCloseEvent *event)
{
    emit changeActionEnable(true);
}

void QWDialogLocate::setSpinRange(int rowCount, int colCount)
{
    ui->spinBox_column->setMaximum(colCount);
    ui->spinBox_row->setMaximum(rowCount);
}

void QWDialogLocate::initSpinValue(int rowNo, int colNo)
{
    ui->spinBox_column->setValue(colNo);
    ui->spinBox_row->setValue(rowNo);
}

void QWDialogLocate::on_btnSetText_clicked()
{
    int row = ui->spinBox_row->value();
    int column = ui->spinBox_column->value();
    QString text = ui->lineEdit->text();
    emit changeCellText(row, column, text);

    if (ui->checkBox_row->isChecked())
        ui->spinBox_row->setValue(1 + ui->spinBox_row->value());
    if (ui->checkBox_column->isChecked())
        ui->spinBox_column->setValue(1 + ui->spinBox_column->value());
}
