#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setCentralWidget(ui->splitterMain);
    label_cell_index_ = new QLabel("current index:", this);
    label_cell_index_->setMinimumWidth(250);
    label_cell_type_ = new QLabel("curent type:", this);
    label_cell_type_->setMinimumWidth(200);
    label_student_id_ = new QLabel("student id:", this);
    label_student_id_->setMinimumWidth(200);

    ui->statusbar->addWidget(label_cell_index_);
    ui->statusbar->addWidget(label_cell_type_);
    ui->statusbar->addWidget(label_student_id_);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_settitle_clicked() {
    QTableWidgetItem *header_item;
    QStringList       header_text;
    header_text << "name"
                << "sex"
                << "birth"
                << "Nation"
                << "score"
                << "parthM";

    ui->tableWidget->setColumnCount(header_text.count());
    for (int i = 0; i < ui->tableWidget->columnCount(); ++i) {
        header_item = new QTableWidgetItem(header_text.at(i));
        QFont font  = header_item->font();
        font.setBold(true);
        font.setPointSize(12);
        header_item->setTextColor(Qt::red);
        header_item->setFont(font);
        ui->tableWidget->setHorizontalHeaderItem(i, header_item);
    }
}

void MainWindow::on_pushButton_init_clicked() {
    QString name, sex;
    bool    isParty{ false };
    QDate   birth{};
    birth.setDate(1980, 4, 7);
    ui->tableWidget->clearContents();
    int rows = ui->tableWidget->rowCount();
    for (int i = 0; i < rows; ++i) {
        name = QString::asprintf("student%d", i);
        if ((i % 2) == 0)
            sex = "male";
        else
            sex = "fmale";
        createItemsARow(i, name, sex, birth, "han", isParty, 70);
        birth   = birth.addDays(20);
        isParty = !isParty;
    }
}

void MainWindow::createItemsARow(
    int row, QString name, QString sex, QDate birth, QString Nation, bool isPM, int score) {
    QTableWidgetItem *item;
    // name
    uint studentid = 201605000;
    item           = new QTableWidgetItem(name, MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    studentid += row;
    item->setData(Qt::UserRole, QVariant(studentid));
    ui->tableWidget->setItem(row, MainWindow::colName, item);

    // sex
    QIcon icon;
    if (sex == "male")
        icon.addFile(":/images/icons/boy.ico");
    else
        icon.addFile(":/images/icons/girl.ico");
    item = new QTableWidgetItem(sex, MainWindow::colSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, colSex, item);

    // birth
    QString str = birth.toString("yyyy-MM-dd");
    item        = new QTableWidgetItem(str, ctBirth);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, colBirth, item);

    // nation
    item = new QTableWidgetItem(Nation, ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, colNation, item);

    // isPary
    item = new QTableWidgetItem("party", ctParthM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    item->setCheckState(isPM ? Qt::Checked : Qt::Unchecked);
    item->setBackgroundColor(Qt::yellow);
    ui->tableWidget->setItem(row, colPartyM, item);

    // score
    str.setNum(score);
    item = new QTableWidgetItem(str, ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableWidget->setItem(row, colScore, item);
}

void MainWindow::on_pushButton_setrownum_clicked() {
    int count = ui->spinBox_rownum->text().toInt();
    ui->tableWidget->setRowCount(count);
}

void MainWindow::on_tableWidget_currentCellChanged(int currentRow,
                                                   int currentColumn,
                                                   int previousRow,
                                                   int previousColumn) {
    QTableWidgetItem *item = ui->tableWidget->item(currentRow, currentColumn);
    if (!item)
        return;
    label_cell_index_->setText(
        QString::asprintf("current index:%d row,  %d column", currentRow, currentColumn));
    label_cell_type_->setText(QString::asprintf("current type:%d", item->type()));
    item   = ui->tableWidget->item(currentRow, colName);
    int id = item->data(Qt::UserRole).toInt();
    label_student_id_->setText(QString::asprintf("student id:%d", id));
}

void MainWindow::on_pushButton_remove_currentrow_clicked() {
    int cur_row = ui->tableWidget->currentRow();
    ui->tableWidget->removeRow(cur_row);
}

void MainWindow::on_pushButton_insert_clicked() {
    int cur_row = ui->tableWidget->currentRow();
    ui->tableWidget->insertRow(cur_row);
    createItemsARow(cur_row,
                    "insert row",
                    "male",
                    QDate::fromString("1990-01-01", "yyyy-MM-dd"),
                    "miao",
                    true,
                    55);
}

void MainWindow::on_pushButton_add_clicked() {
    int cur_row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(cur_row);
    createItemsARow(cur_row,
                    "appen row",
                    "female",
                    QDate::fromString("2000-1-1", "yyyy-M-d"),
                    "man",
                    false,
                    77);
}

void MainWindow::on_pushButton_autorow_clicked() {
    ui->tableWidget->resizeRowsToContents();
}

void MainWindow::on_pushButton_autocol_clicked() {
    ui->tableWidget->resizeColumnsToContents();
}

void MainWindow::on_checkBox_item_editable_clicked(bool checked) {
    if (checked)
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked
                                         | QAbstractItemView::SelectedClicked);
    else
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_checkBox_background_clicked(bool checked) {
    ui->tableWidget->setAlternatingRowColors(checked);
}

void MainWindow::on_checkBox_show_rowtitle_clicked(bool checked) {
    ui->tableWidget->verticalHeader()->setVisible(checked);
}

void MainWindow::on_checkBox_show_coltitle_clicked(bool checked) {
    ui->tableWidget->horizontalHeader()->setVisible(checked);
}

void MainWindow::on_radioButton_select_row_clicked(bool checked) {
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::on_radioButton_select_item_clicked(bool checked) {
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}

void MainWindow::on_pushButton_read_clicked() {
    QString           str;
    QTableWidgetItem *cell_item;
    ui->plainTextEdit->clear();
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        str = QString::asprintf("index: %02d: ", i + 1);
        for (int j = 0; j < ui->tableWidget->columnCount() - 1; ++j) {
            cell_item = ui->tableWidget->item(i, j);
            str       = str + cell_item->text() + "     ";
        }
        cell_item = ui->tableWidget->item(i, colPartyM);
        if (cell_item->checkState() == Qt::Checked)
            str += "party";
        else
            str += "normal";
        ui->plainTextEdit->appendPlainText(str);
    }
}
