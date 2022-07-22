#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private:
    bool openTextByIODevice(const QString &aFileName);
    bool saveTextByIODevice(const QString &aFileName);

    bool openTextByStream(const QString &aFileName);
    bool saveTextByStream(const QString &aFileName);

private slots:
    void on_action_file_open_triggered();
    void on_action_file_saveas_triggered();

    void on_action_stream_open_triggered();
    void on_action_stream_saveas_triggered();

private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
