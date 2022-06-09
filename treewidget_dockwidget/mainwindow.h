#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTreeWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initTree();
    void initSignalSlot();
    void addFolderItem(QTreeWidgetItem *item, QString dir_name);
    QString getFinalFolderName(const QString &path_name);
    void addImageItem(QTreeWidgetItem *item, QString file_name);
    void displayImage(QTreeWidgetItem *item);
    void changeItemCaption(QTreeWidgetItem *item);

private slots:
    void onActionAddFolderTriggered();
    void onActionAddFilesTriggered();
    void onCurrentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);
    void onActionDeleteItemTriggered();

private:
    enum TreeItemType { kTopItem = 1001, kGroupItem, kImageItem };
    enum TreeColType { kColItem = 0, kColType };

    QLabel *label_file_name_;

    QPixmap cur_pixmap_;
    float pix_ratio_;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
