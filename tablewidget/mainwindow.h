#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_settitle_clicked();

    void on_pushButton_init_clicked();

    void on_pushButton_setrownum_clicked();

    void on_tableWidget_currentCellChanged(int currentRow,
                                           int currentColumn,
                                           int previousRow,
                                           int previousColumn);

    void on_pushButton_remove_currentrow_clicked();

    void on_pushButton_insert_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_autorow_clicked();

    void on_pushButton_autocol_clicked();

    void on_checkBox_item_editable_clicked(bool checked);

    void on_checkBox_background_clicked(bool checked);

    void on_checkBox_show_rowtitle_clicked(bool checked);

    void on_checkBox_show_coltitle_clicked(bool checked);

    void on_radioButton_select_row_clicked(bool checked);

    void on_radioButton_select_item_clicked(bool checked);

    void on_pushButton_read_clicked();

private:
    void createItemsARow(
        int row, QString name, QString sex, QDate birth, QString Nation, bool isPM, int score);

private:
    enum CellType { ctName = 1000, ctSex, ctBirth, ctNation, ctParthM, ctScore };
    enum FiledColNum { colName, colSex, colBirth, colNation, colScore, colPartyM };

    QLabel *label_cell_index_;
    QLabel *label_cell_type_;
    QLabel *label_student_id_;

    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
