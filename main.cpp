#include "millmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MillMainWindow w;
    w.show();
    return a.exec();
}
