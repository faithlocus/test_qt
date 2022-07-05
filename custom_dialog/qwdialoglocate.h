#ifndef QWDIALOGLOCATE_H
#define QWDIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class QWDialogLocate;
}

class QWDialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogLocate(QWidget *parent = nullptr);
    ~QWDialogLocate();
    void setSpinRange(int rowCount, int colCount);

signals:
    void changeCellText(int row, int column, QString text);
    void changeActionEnable(bool en);

public slots:
    void initSpinValue(int rowNo, int colNo);

private slots:
    void on_btnSetText_clicked();

private:
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::QWDialogLocate *ui;
};

#endif // QWDIALOGLOCATE_H
