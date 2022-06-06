#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushbtn_now_clicked();

    void on_calendarWidget_currentPageChanged(int year, int month);

    void on_calendarWidget_selectionChanged();

    void on_pushButton_timer_set_clicked();

    void on_pushButton_start_timer_clicked();

    void on_pushButton_stop_timer_clicked();

    void timer_timeout();

private:
    Ui::MainWindow *ui;
    QTimer timer;
};
#endif // MAINWINDOW_H
