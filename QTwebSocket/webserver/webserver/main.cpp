#include "webserver.h"
#include <QtWidgets/QApplication>
#include <QtWebSockets/QtWebSockets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    webserver w;
    w.show();


    return a.exec();
}
