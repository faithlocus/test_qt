#include "qdlglogin.h"
#include "ui_qdlglogin.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QMouseEvent>
#include <QSettings>

QDlgLogin::QDlgLogin(QWidget *parent) : QDialog(parent), ui(new Ui::QDlgLogin) {
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::SplashScreen);
    readSettings();
}

QDlgLogin::~QDlgLogin() {
    delete ui;
}

void QDlgLogin::readSettings() {
    QString   organization = "WWB-Qt";
    QString   appName      = "Samp6-5";
    QSettings settings(organization, appName);
    m_user              = settings.value("Username", "user").toString();
    QString defaultPWSD = encrypt("12345");
    m_pswd              = settings.value("PSWD", defaultPWSD).toString();
    bool saved          = settings.value("saved", false).toBool();
    if (saved)
        ui->lineEdit_username->setText(m_user);
    ui->checkBox_save->setChecked(saved);
}

void QDlgLogin::writeSettings() {
    QSettings settings("WWB-Qt", "samp6-5");
    settings.setValue("Username", m_user);
    settings.setValue("PSWD", m_pswd);
    settings.setValue("saved", ui->checkBox_save->isChecked());
}

QString QDlgLogin::encrypt(const QString &str) {
    QByteArray btArrary;
    btArrary.append(str);
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(btArrary);
    QByteArray resultArray = hash.result();
    QString    md5         = resultArray.toHex();
    return md5;
}
void QDlgLogin::on_pushButton_ok_clicked() {
    QString user        = ui->lineEdit_username->text().trimmed();
    QString pswd        = ui->lineEdit_password->text().trimmed();
    QString encryptPSWD = encrypt(pswd);
    if (user == m_user && pswd == m_pswd) {
        writeSettings();
        accept();
    } else {
        ++m_tryCount;
        if (m_tryCount > 3) {
            QMessageBox::critical(this, "错误", "输入错误次数太多，强行退出");
            reject();
        } else {
            QMessageBox::warning(this, "错误", "用户名或密码错误");
        }
    }
}

void QDlgLogin::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        m_moving  = true;
        m_lastPos = event->globalPos() - pos();
    }
    return QDialog::mousePressEvent(event);
}

void QDlgLogin::mouseMoveEvent(QMouseEvent *event) {
    if (m_moving && event->buttons() && Qt::LeftButton
        && (event->globalPos() - m_lastPos).manhattanLength() > QApplication::startDragDistance()) {
        move(event->globalPos() - m_lastPos);
        m_lastPos = event->globalPos() - pos();
        return QDialog::mouseMoveEvent(event);
    }
}

void QDlgLogin::mouseReleaseEvent(QMouseEvent *event) {
    m_moving = false;
}
