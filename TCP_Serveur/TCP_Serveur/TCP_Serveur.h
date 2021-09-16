#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TCP_Serveur.h"

class TCP_Serveur : public QMainWindow
{
    Q_OBJECT

public:
    TCP_Serveur(QWidget *parent = Q_NULLPTR);

private:
    Ui::TCP_ServeurClass ui;
};
