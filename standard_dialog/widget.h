#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_open_clicked();

    void on_pushButton_opens_clicked();

    void on_pushButton_sel_folder_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_sel_color_clicked();

    void on_pushButton_sel_font_clicked();

    void on_pushButton_input_str_clicked();

    void on_pushButton_input_int_clicked();

    void on_pushButton_input_double_clicked();

    void on_pushButton_input_item_clicked();

    void on_pushButton_question_clicked();

    void on_pushButton_information_clicked();

    void on_pushButton_warning_clicked();

    void on_pushButton_critical_clicked();

    void on_pushButton_abort_clicked();

private:
    Ui::Widget *ui;
};
#endif  // WIDGET_H
