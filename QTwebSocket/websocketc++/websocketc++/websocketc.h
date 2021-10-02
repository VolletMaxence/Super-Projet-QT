#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_websocketc.h"

class websocketc : public QMainWindow
{
    Q_OBJECT

public:
    websocketc(QWidget *parent = Q_NULLPTR);

private:
    Ui::websocketcClass ui;
};
