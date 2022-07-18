#include "qformdoc.h"
#include "ui_qformdoc.h"

#include <QFile>
#include <QFileInfo>
#include <QFontDialog>
#include <QMessageBox>
#include <QTextStream>

QFormDoc::QFormDoc(QWidget *parent) : QWidget(parent), ui(new Ui::QFormDoc) {
    ui->setupUi(this);
    setWindowTitle("New Doc");
    setAttribute(Qt::WA_DeleteOnClose);
}

QFormDoc::~QFormDoc() {
    QMessageBox::information(this, "信息", " 文档窗口被释放");
    delete ui;
}

void QFormDoc::loadFromFile(const QString &name) {
    QFile file(name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        ui->plainTextEdit->clear();
        ui->plainTextEdit->setPlainText(stream.readAll());
        file.close();
        current_file_ = name;
        QFileInfo file_info(name);
        QString   str = file_info.fileName();
        this->setWindowTitle(str);
        file_opend_ = true;
    }
}

void QFormDoc::setEditFont() {
    QFont font = ui->plainTextEdit->font();
    bool  ok;
    font = QFontDialog::getFont(&ok, font);
    ui->plainTextEdit->setFont(font);
}

void QFormDoc::textCut() {
    ui->plainTextEdit->cut();
}

void QFormDoc::textCopy() {
    ui->plainTextEdit->copy();
}

void QFormDoc::textPaste() {
    ui->plainTextEdit->paste();
}
