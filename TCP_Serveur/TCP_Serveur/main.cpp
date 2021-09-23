#include "TCP_Serveur.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCP_Serveur w;
    w.show();
    return a.exec();
}