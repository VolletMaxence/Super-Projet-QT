#include "websocketc.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    websocketc w;
    w.show();
    return a.exec();
}
