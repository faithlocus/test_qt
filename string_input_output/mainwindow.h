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

private slots:
  void on_pb_calc_clicked();

  void on_le_2_textChanged(const QString &arg1);

  void on_le_8_textChanged(const QString &arg1);

  void on_le_10_textChanged(const QString &arg1);

  void on_le_16_textChanged(const QString &arg1);

  void updateNum();

  void on_le_2_editingFinished();

  void on_le_10_editingFinished();

  private:
  Ui::MainWindow *ui;
  int num_;
};
#endif // MAINWINDOW_H
