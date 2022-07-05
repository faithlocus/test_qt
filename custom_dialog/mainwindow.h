#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QItemSelectionModel>
#include <QStandardItemModel>

#include "qwdialogheaders.h"
#include "qwdialoglocate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setDlgLocatNull();

private:
    void closeEvent(QCloseEvent *event);
    void initSignalSlots();

signals:
    void cellIndexChanged(int row, int column);
private slots:
    void onActionCountTriggered();
    void onActionHeadersTriggered();
    void onActionLocateTriggered();
    void on_tableView_clicked(const QModelIndex &index);

    void setACellText(int row, int column, QString text);
    void setLocateEnable(bool flag);

private:
    Ui::MainWindow *ui;

    QStandardItemModel *theModel;
    QItemSelectionModel *theSelection;

    QWDialogHeaders *dlgheaders;
    QWDialogLocate *dlglocate;
};
#endif // MAINWINDOW_H
