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

private:
    void paintEvent(QPaintEvent *event);

private:
    Ui::QwMainWindow *ui;
};
#endif  // QWMAINWINDOW_H
