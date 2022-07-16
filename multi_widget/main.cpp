#include "qwmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QwMainWindow w;
    w.show();
    return a.exec();
}
