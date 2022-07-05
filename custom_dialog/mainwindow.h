#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelectionModel>
#include <QStandardItemModel>

#include "qwdialogheaders.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initSignalSlots();

private slots:
    void onActionCountTriggered();
    void onActionHeadersTriggered();

private:
    Ui::MainWindow *ui;

    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;

    QWDialogHeaders *dlgheaders;
};
#endif // MAINWINDOW_H
