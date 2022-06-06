#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QSpinBox>
#include <QFontComboBox>

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
    void on_actionbold_toggled(bool arg1);
    void on_textEdit_copyAvailable(bool b);
    void on_textEdit_selectionChanged();
    void on_actionitalic_triggered(bool checked);
    void on_actionunder_triggered(bool checked);
    void onSpinBoxFontSizeValueChanged(int size);
    void onComboboxFontIndexChanged(const QString &str);

private:
    void initUI();
    void initSignalSlots();


private:
    QLabel *lab_curfile_;
    QProgressBar *prograsbar_;
    QSpinBox *font_size_;
    QFontComboBox *font_;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
