#include "ClientQT.h"
#include "user.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientQT w;
    w.show();
    return a.exec();
}
