#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class QListWidgetItem;

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
    void setActionForButton();
    void createSelectionPopMenu();

private slots:
    void onActionListInitTriggered();
    void onActionInsertTriggered();
    void onActionDeleteTriggered();
    void onActionClearTriggered();
    void onActionSelectAll();
    void onActionSelectNone();
    void onActionSelectInverse();
    void onListwidgetCurrentItemChanged(QListWidgetItem *current, QListWidgetItem *pre);
    void onListwidgetCustomContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
