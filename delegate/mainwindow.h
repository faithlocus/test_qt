#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelectionModel>
#include <QLabel>
#include <QMainWindow>
#include <QStandardItemModel>

#include "qwcomboboxdelegate.h"
#include "qwfloatspindelegate.h"
#include "qwinputspindelegate.h"

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

private:
    void initModelFromStringList(QStringList &);

private slots:
    void on_currentChanged(const QModelIndex &current, const QModelIndex &previous);
    void onActionOpenTriggered();
    void onActionAppendTriggered();
    void onActionDeleteTriggered();
    void onActionAlignLeftTriggered();
    void onActionAlignBoldTriggered();
    void onActionPreviewTriggered();
    void onActionSaveTriggered();

private:
    QLabel *label_current_file_;
    QLabel *label_cell_pos_;
    QLabel *label_cell_text_;

    QStandardItemModel * theModel;
    QItemSelectionModel *theSelection;

    QWInputSpinDelegate intSpinDelegate;
    QWFloatSpinDelegate floatSpinDelegate;
    QWComboboxDelegate  comboboxDelegate;
    Ui::MainWindow *    ui;
};
#endif  // MAINWINDOW_H
