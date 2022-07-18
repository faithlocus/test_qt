#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

namespace Ui {
class QFormDoc;
}

class QFormDoc : public QWidget {
    Q_OBJECT

private:
    QString current_file_;
    bool    file_opend_{ false };

public:
    explicit QFormDoc(QWidget *parent = nullptr);
    ~QFormDoc();

    QString currentFileName() const {
        return current_file_;
    }

    bool isFileOpened() const {
        return file_opend_;
    }

    void loadFromFile(const QString &name);
    void setEditFont();
    void textCut();
    void textCopy();
    void textPaste();

private:
    Ui::QFormDoc *ui;
};

#endif  // QFORMDOC_H
