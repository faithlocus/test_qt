#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>

#include "../delegate/qwcomboboxdelegate.h"
#include "../delegate/qwfloatspindelegate.h"
#include "../delegate/qwinputspindelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

#define FixedColumnCount 6

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_save_stm_triggered();
    void on_action_open_stm_triggered();
    void on_action_open_dat_triggered();
    void on_action_save_dat_triggered();

private:
    void resetTable(int aRowCount);
    bool saveDataAsStream(QString &aFileName);
    bool openDataAsStream(QString &aFileName);
    bool saveBinaryFile(QString &aFileName);
    bool openBinaryFile(QString &aFileName);

private:
    QLabel *             LabCellPos;
    QLabel *             LabCellText;
    QWInputSpinDelegate  intSpinDelegate;
    QWFloatSpinDelegate  floatSpinDelegate;
    QWComboboxDelegate   comboBoxDelegate;
    QStandardItemModel * theModel;
    QItemSelectionModel *theSelection;
    Ui::MainWindow *     ui;
};
#endif  // MAINWINDOW_H
