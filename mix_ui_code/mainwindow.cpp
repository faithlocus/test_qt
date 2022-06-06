#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();
    initSignalSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // statusbar
    lab_curfile_ = new QLabel();
    lab_curfile_->setMinimumWidth(150);
    lab_curfile_->setText("current file:");
    ui->statusbar->addWidget(lab_curfile_);

    prograsbar_ = new QProgressBar();
    prograsbar_->setMaximumWidth(200);
    prograsbar_->setMinimum(5);
    prograsbar_->setMaximum(50);
    prograsbar_->setValue(ui->textEdit->font().pointSize());
    ui->statusbar->addWidget(prograsbar_);

    // toolbar
    font_size_ = new QSpinBox;
    font_size_->setMinimum(5);
    font_size_->setMaximum(50);
    font_size_->setValue(ui->textEdit->font().pointSize());
    font_size_->setMinimumWidth(50);
    ui->toolBar->addWidget(new QLabel("font size:"));
    ui->toolBar->addWidget(font_size_);

    ui->toolBar->addSeparator();
    ui->toolBar->addWidget(new QLabel("font:"));
    font_ = new QFontComboBox;
    font_->setMinimumWidth(150);
    ui->toolBar->addWidget(font_);

    setCentralWidget(ui->textEdit);
}

void MainWindow::initSignalSlots()
{
    connect(font_size_,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(onSpinBoxFontSizeValueChanged(int)),
            Qt::UniqueConnection);
    connect(font_,
            SIGNAL(currentIndexChanged(const QString &)),
            this,
            SLOT(onComboboxFontIndexChanged(const QString &)),
            Qt::UniqueConnection);
}

void MainWindow::on_actionbold_toggled(bool arg1)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    if (arg1)
        fmt.setFontWeight(QFont::Bold);
    else
        fmt.setFontWeight(QFont::Normal);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionitalic_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontItalic(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionunder_triggered(bool checked)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontUnderline(checked);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_textEdit_copyAvailable(bool b)
{
    ui->actioncut->setEnabled(b);
    ui->actioncopy->setEnabled(b);
    ui->actionpaste->setEnabled(ui->textEdit->canPaste());
}

void MainWindow::on_textEdit_selectionChanged()
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    ui->actionbold->setChecked(fmt.font().bold());
    ui->actionitalic->setChecked(fmt.font().italic());
    ui->actionunder->setChecked(fmt.font().underline());
}

void MainWindow::onSpinBoxFontSizeValueChanged(int size)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontPointSize(size);
    ui->textEdit->mergeCurrentCharFormat(fmt);
    prograsbar_->setValue(size);
}

void MainWindow::onComboboxFontIndexChanged(const QString &str)
{
    QTextCharFormat fmt;
    fmt = ui->textEdit->currentCharFormat();
    fmt.setFontFamily(str);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}
