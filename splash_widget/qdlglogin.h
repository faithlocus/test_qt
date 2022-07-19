#ifndef QDLGLOGIN_H
#define QDLGLOGIN_H

#include <QDialog>

namespace Ui {
class QDlgLogin;
}

class QDlgLogin : public QDialog {
    Q_OBJECT
private:
    bool    m_moving{ false };
    QPoint  m_lastPos;
    QString m_user = "user";
    QString m_pswd = "12345";
    int     m_tryCount{ 0 };

    void    readSettings();
    void    writeSettings();
    QString encrypt(const QString &str);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit QDlgLogin(QWidget *parent = nullptr);
    ~QDlgLogin();

private slots:
    void on_pushButton_ok_clicked();

private:
    Ui::QDlgLogin *ui;
};

#endif  // QDLGLOGIN_H
