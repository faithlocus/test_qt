#ifndef MDIMAINWINDOW_H
#define MDIMAINWINDOW_H

#include <QMainWindow>
#include <QMdiSubWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MDIMainWindow;
}
QT_END_NAMESPACE

class MDIMainWindow : public QMainWindow {
    Q_OBJECT

public:
    MDIMainWindow(QWidget *parent = nullptr);
    ~MDIMainWindow();

private slots:
    void on_action_new_triggered();

    void on_action_open_triggered();

    void on_action_mdi_triggered(bool checked);

    void on_action_cascade_triggered();

    void on_action_tile_triggered();

    void on_action_close_all_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

    void on_action_cut_triggered();

    void on_action_font_triggered();

private:
    Ui::MDIMainWindow *ui;
};
#endif  // MDIMAINWINDOW_H
