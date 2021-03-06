#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class QwMainWindow;
}
QT_END_NAMESPACE

class QwMainWindow : public QMainWindow {
    Q_OBJECT

public:
    QwMainWindow(QWidget *parent = nullptr);
    ~QwMainWindow();

private slots:
    void on_action_insidewidget_triggered();
    void on_action_widget_triggered();
    void on_action_insidemainwindow_triggered();
    void on_action_mainwindow_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_tabWidget_tabCloseRequested(int index);

private:
    void initSignalSlot();
    void paintEvent(QPaintEvent *event);

private:
    Ui::QwMainWindow *ui;
};
#endif  // QWMAINWINDOW_H
