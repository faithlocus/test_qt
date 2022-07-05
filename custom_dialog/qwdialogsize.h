#ifndef QWDIALOGSIZE_H
#define QWDIALOGSIZE_H

#include <QDialog>

namespace Ui {
class QWDialogSize;
}

class QWDialogSize : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogSize(QWidget *parent = nullptr);
    ~QWDialogSize();

    int rowCount() const;
    int columnCount() const;
    void setRowColumn(int row, int column);

private:
    Ui::QWDialogSize *ui;
};

#endif // QWDIALOGSIZE_H
